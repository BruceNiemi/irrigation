import './App.css'
import { useEffect, useState } from 'react'
import { Card, CardContent, CardHeader, CardTitle } from './components/ui/card'
import { DisplayCard } from './components/ui/displaycard'
import { Chart } from './components/ui/chart'

interface SensorData {
  timestamp: string;
  moisture: number;
  temperature: number;
}

interface Info {
  state: string;
  valve: boolean;
  sensor: SensorData | null;
}

function App() {
  const [moistureData, setMoistureData] = useState<number[]>([]);
  const [temperatureData, setTemperatureData] = useState<number[]>([]);
  const [timestamps, setTimestamps] = useState<string[]>([]);
  const [systemState, setSystemState] = useState<string>("Unknown");
  const [operationMode, setOperationMode] = useState<string>("Unknown");
  const [valveStatus, setValveStatus] = useState<string>("Unknown");

  useEffect(() => {
    const socket = new WebSocket("ws://localhost:7070/real-time/")

    socket.onmessage = (event) => {
      const infoData: Info = JSON.parse(event.data);

      if (infoData.sensor) {
        const sensorData = infoData.sensor;
        setTimestamps(prevTimestamps => [...prevTimestamps, sensorData.timestamp].slice(-5));
        setMoistureData(prevMoistureData => [...prevMoistureData, sensorData.moisture].slice(-5));
        setTemperatureData(prevTemperatureData => [...prevTemperatureData, sensorData.temperature].slice(-5));
      }


      setSystemState(infoData.state);
      setOperationMode(infoData.sensor ? "Sensor" : "Timer");
      setValveStatus(infoData.valve ? "Open" : "Closed");
    }

    return () => {
      socket.close();
    };
  }, []);

  return (
    <div className='m-4 space-y-7'>
      <div className="grid gap-4 md:grid-cols-2 lg:grid-cols-4">
        <DisplayCard
          title="State"
          description="Current operational state of the system."
          value={systemState}
        />

        <DisplayCard
          title="Mode"
          description="Current operation mode of the system."
          value={operationMode}
        />

        <DisplayCard
          title="Valve"
          description="Current status of the valve."
          value={valveStatus}
        />
      </div>
      <div>
        <div className='grid gap-4 md:grid-cols-1 lg:grid-cols-2'>
          <Card>
            <CardHeader className="col-span-2">
              <CardTitle>Moisture</CardTitle>
            </CardHeader>
            <CardContent className="pl-2">
              <Chart
                x="moisture"
                xAxisKey="time"
                yAxisLabel='Moisture Content (%)'
                data={moistureData.map((moisture, index) => ({
                  time: timestamps[index],
                  moisture: moisture
                }))}
              />
            </CardContent>
          </Card>
          <Card>
            <CardHeader className="col-span-2">
              <CardTitle>Temperature</CardTitle>
            </CardHeader>
            <CardContent className='pl-2'>
              <Chart
                x="temp"
                xAxisKey="time"
                yAxisLabel="Temperature (°C)"
                data={temperatureData.map((temp, index) => ({
                  time: timestamps[index],
                  temp: temp
                }))}
              />
            </CardContent>
          </Card>
        </div>
      </div>
    </div>
  )
}

export default App
