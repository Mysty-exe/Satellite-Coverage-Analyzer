import './App.css';
// Suppress missing declaration file for the wasm module
// @ts-ignore
import createModule from './wasm/SatelliteCoverage.js';
import Simulation from './Simulation.js';

// const Module = await createModule();

function App() {
  

  return (
    <div>
      <Simulation />
    </div>
  );
}

export default App
