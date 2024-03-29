/*
 * This Kotlin source file was generated by the Gradle 'init' task.
 */
package gg.bruce.irrigation

import com.fazecast.jSerialComm.SerialPort
import io.javalin.Javalin
import io.javalin.websocket.WsContext
import java.time.LocalDateTime
import java.time.format.DateTimeFormatter
import java.util.*
import java.util.concurrent.BlockingQueue
import java.util.concurrent.Executors
import java.util.concurrent.LinkedBlockingQueue
import java.util.concurrent.TimeUnit
import kotlin.system.exitProcess

private val dataQueue: BlockingQueue<String> = LinkedBlockingQueue()
private val clients = ArrayList<WsContext>()
private val formatter = DateTimeFormatter.ofPattern("HH:mm:ss")

fun main() {
    val serialPort = SerialPort.getCommPorts()[0]
    serialPort.setBaudRate(115200)
    serialPort.setComPortTimeouts(SerialPort.TIMEOUT_SCANNER, 0, 0)
    if (!serialPort.openPort()) {
        exitProcess(-1)
    }

    Thread {
        val scanner = Scanner(serialPort.inputStream)

        while (scanner.hasNextLine()) {
            val line = scanner.nextLine()

            if (!line.startsWith("DATA: ") || !line.endsWith("END")) {
                continue
            }
            println(line)
            dataQueue.add(line)
        }
    }.start()


    val app = Javalin.create()
        .ws("/real-time/") {
            it.onConnect { ctx ->
                println("new connection")
                clients.add(ctx)
            }
        }.start(7070)

    val scheduler = Executors.newScheduledThreadPool(1)
    scheduler.scheduleWithFixedDelay({ send() }, 0, 1, TimeUnit.SECONDS)
}

fun send() {
    println("sending?")
    val data = parseStringData(dataQueue.poll()) ?: return
    clients.forEach {
        it.send(data)
    }
}

fun parseStringData(input: String?): Info? {
    if (input == null) return null

    val regex = Regex("""s='([^']+)'(?: m='([^']+)')?(?: t='([^']+)')?(?: v='(\d)')?""")

    val matchResult = regex.find(input) ?: return null

    val (state, moisture, temperature, valve) = matchResult.destructured

    val currentTime = LocalDateTime.now()
    val formattedTime = formatter.format(currentTime)

    val sensorData = if (moisture.isNotEmpty() && temperature.isNotEmpty()) {
        SensorData(formattedTime, moisture.toDouble(), temperature.toDouble())
    } else {
        null
    }

    return Info(state, valve.toBoolean(), sensorData)
}

data class Info(val state: String, val valve: Boolean, val sensor: SensorData?)
data class SensorData(val timestamp: String, val moisture: Double, val temperature: Double)