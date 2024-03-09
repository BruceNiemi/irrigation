import './App.css'
import { DisplayCard } from './components/ui/displaycard'

function App() {
  return (
    <div className='bg-slate-100 min-h-screen'>
      <div className="mx-auto grid gap-4 md:grid-cols-2 lg:grid-cols-4 content-center">
        <DisplayCard
          title="State"
          description="Current operational state of the system"
          value="Unknown"
        />

        <DisplayCard
          title="Mode"
          description="Current operation mode of the system (Timer or Sensor)"
          value="Timer"
        />

        <DisplayCard
          title="Valve"
          description="Current status of the valve (open or closed)"
          value="Open"
        />
      </div>
    </div>
  )
}

export default App
