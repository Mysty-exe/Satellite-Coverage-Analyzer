import './App.css';
// Suppress missing declaration file for the wasm module
// @ts-ignore
import createModule from './wasm/SatelliteCoverage.js';
  
const Module = await createModule();

function App() {
  return (
    <div>
      <h1>{"Isn't working huh...?"}</h1>
      <p>{Module.loadData()}</p>
    </div>
  )
}

export default App
