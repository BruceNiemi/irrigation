import './App.css'
import { Card, CardContent, CardHeader, CardTitle } from './components/ui/card'
import { DisplayCard } from './components/ui/displaycard'
import { Chart } from './components/ui/chart'

const temp_data = [
  {
    time: "8:00",
    temp: 30.5
  },
  {
    time: "9:00",
    temp: 32.4
  },
  {
    time: "10:00",
    temp: 20.6
  },
  {
    time: "11:00",
    temp: 25.2
  },
  {
    time: "12:00",
    temp: 28.0
  },
  {
    time: "13:00",
    temp: 26.8
  },
  {
    time: "14:00",
    temp: 29.5
  },
  {
    time: "15:00",
    temp: 31.2
  },
  {
    time: "16:00",
    temp: 27.4
  },
  {
    time: "17:00",
    temp: 23.8
  }
]

const moisture_data = [
  {
    time: "08:00",
    moisture: 0.6
  },
  {
    time: "09:00",
    moisture: 0.3
  },
  {
    time: "10:00",
    moisture: 0.8
  },
  {
    time: "11:00",
    moisture: 0.4
  },
  {
    time: "12:00",
    moisture: 0.6
  },
  {
    time: "13:00",
    moisture: 0.7
  },
  {
    time: "14:00",
    moisture: 0.5
  },
  {
    time: "15:00",
    moisture: 0.9
  },
  {
    time: "16:00",
    moisture: 0.3
  },
  {
    time: "17:00",
    moisture: 0.2
  }
];


function App() {
  return (
    <div className='m-4 space-y-7'>
      <div className="grid gap-4 md:grid-cols-2 lg:grid-cols-4">
        <DisplayCard
          title="State"
          description="Current operational state of the system."
          value="Unknown"
        />

        <DisplayCard
          title="Mode"
          description="Current operation mode of the system."
          value="Timer"
        />

        <DisplayCard
          title="Valve"
          description="Current status of the valve."
          value="Open"
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
                data={moisture_data}
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
                data={temp_data}
              />
            </CardContent>
          </Card>
        </div>
      </div>
    </div>
  )
}

export default App
