import './App.css'
import { useEffect, useState } from 'react'
import { Card, CardContent, CardHeader, CardTitle } from './components/ui/card'
import { DisplayCard } from './components/ui/displaycard'
import { Chart } from './components/ui/chart'

interface SensorData {
  open: boolean;
  moisture: number;
  temp: number;
}

interface Info {
  timestamp: string;
  sensor: SensorData;
}

function App() {
  const [moistureData, setMoistureData] = useState<number[]>([]);
  const [temperatureData, setTemperatureData] = useState<number[]>([]);
  const [timestamps, setTimestamps] = useState<string[]>([]);
  const [valveStatus, setValveStatus] = useState<string>("Unknown");

  useEffect(() => {
    const socket = new WebSocket("ws://localhost:7070/real-time/")

    socket.onmessage = (event) => {
      const infoData: Info = JSON.parse(event.data);

      const sensorData = infoData.sensor;
      setTimestamps(prevTimestamps => [...prevTimestamps, infoData.timestamp].splice(-5));
      setMoistureData(prevMoistureData => [...prevMoistureData, sensorData.moisture].splice(-5));
      setTemperatureData(prevTemperatureData => [...prevTemperatureData, sensorData.temp].splice(-5));
  
      setValveStatus(sensorData.open ? "Open" : "Closed");
    }

    return () => {
      socket.close();
    };
  }, []);

  return (
    <div className='m-4 space-y-7'>
      <div className="grid gap-4 md:grid-cols-2 lg:grid-cols-4">
        <DisplayCard
          title="Sensor Status"
          description="Sensor status of the sensor."
          value={"Connected"}
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
