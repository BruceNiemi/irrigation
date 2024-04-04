/*
 * This Kotlin source file was generated by the Gradle 'init' task.
 */
package gg.bruce.irrigation

import com.fazecast.jSerialComm.SerialPort
import com.google.gson.GsonBuilder
import com.google.gson.JsonSyntaxException
import com.google.gson.stream.MalformedJsonException
import io.javalin.Javalin
import io.javalin.websocket.WsContext
import java.time.LocalDateTime
import java.time.format.DateTimeFormatter
import java.util.*
import java.util.concurrent.BlockingQueue
import java.util.concurrent.Executors
import java.util.concurrent.LinkedBlockingQueue
import kotlin.system.exitProcess

private val dataQueue: BlockingQueue<Info> = LinkedBlockingQueue()
private var clients: WsContext? = null
private val gson = GsonBuilder().create()
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
            try {
                val parsed = gson.fromJson(line, Sensor::class.java)
                val currentTime = LocalDateTime.now()
                val formattedTime = formatter.format(currentTime)
                dataQueue.offer(Info(formattedTime, parsed))
            } catch (ex: Exception) {
                println("error")
            }
        }
    }.start()


    val app = Javalin.create()
        .ws("/real-time/") {
            it.onConnect { ctx ->
                clients = ctx
            }
        }.start(7070)

    val timer = Timer()
    timer.scheduleAtFixedRate(buildTimer(), 0, 1000)
}

fun buildTimer(): TimerTask {
    return object : TimerTask() {
        override fun run() {
            if (!dataQueue.isEmpty()) {
                clients?.send(dataQueue.poll())
            }
        }
    }
}

data class Info(val timestamp: String, val sensor: Sensor)
data class Sensor(val open: Boolean, val moisture: Double, val temp: Double)

//fun send() {
//    println("sending?")
//    val data = parseStringData(dataQueue.take()) ?: return
//    clients?.send(data)
//}

//fun parseStringData(input: String?): Info? {
//    if (input == null) return null
//
//    val regex = Regex("""s='([^']+)'(?: m='([^']+)')?(?: t='([^']+)')?(?: v='(\d)')?""")
//
//    val matchResult = regex.find(input) ?: return null
//
//    val (state, moisture, temperature, valve) = matchResult.destructured
//
//    val currentTime = LocalDateTime.now()
//    val formattedTime = formatter.format(currentTime)
//
//    val sensorData = if (moisture.isNotEmpty() && temperature.isNotEmpty()) {
//        SensorData(formattedTime, moisture.toDouble(), temperature.toDouble())
//    } else {
//        null
//    }
//
//    return Info(state, valve.toBoolean(), sensorData)
//}

//data class Info(val state: String, val valve: Boolean, val sensor: SensorData?)
//data class SensorData(val timestamp: String, val moisture: Double, val temperature: Double)