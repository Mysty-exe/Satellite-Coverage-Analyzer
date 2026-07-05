import './App.css';
import { useState, useEffect } from 'react';
// Suppress missing declaration file for the wasm module
// @ts-ignore
import createModule from './wasm/SatelliteCoverage.js';
import getTLE from './db.ts';
import ListGroup from './Components/ListGroup.tsx';

const Module = await createModule();

const arr = Module.getSatelliteGroups();
const satelliteGroups: string[] = [];
for (let i = 0; i < arr.size(); i++) {
  satelliteGroups.push(arr.get(i));
}
arr.delete();

function App() {
  const [satellites, setSatellites] = useState<Record<string, string[]>>({});

  useEffect(() => {
  satelliteGroups.forEach(async (group) => {
    const data = await getTLE(group);

    const vec = Module.getSatellitesDTO(group, data);

    const arr: string[] = [];

    for (let i = 0; i < vec.size(); i++) {
      arr.push(vec.get(i).name);
    }

    vec.delete();

    setSatellites(prev => ({
      ...prev,
      [group]: arr
      }));
    });
  }, []);

  return (
  <div>
    {satelliteGroups.map((group: string) => (
      <ListGroup key={group} heading={group} items={satellites[group] ?? ['dsfjklsdf']} />
    ))}
  </div>
);
}

export default App
