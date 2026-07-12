import './App.css';
import Simulation from './Simulation.js';
import { useEffect, useState } from 'react';
// @ts-ignore
import createModule from './wasm/SatelliteCoverage.js';
import { loadTLE, getTLE } from './db.js';

const Module = await createModule();

type Satellite = {
    name: string;
    lat: number;
    lon: number;
    alt: number;
};

const arr = Module.getSatelliteGroups();
const satelliteGroups: string[] = [];
for (let i = 0; i < arr.size(); i++) {
  satelliteGroups.push(arr.get(i));
}
arr.delete();

function App() {
  const [satellites, setSatellites] = useState<Satellite[]>([]);

  useEffect(() => {
    async function load() {
          await Promise.all(
          satelliteGroups.map(async (group) => {
              await loadTLE(group);

              const data = await getTLE(group);
              Module.initializeSatelliteGroup(group, data);
          })
        );
      }

      load();
  }, []);

  useEffect(() => {
    const interval = setInterval(async () => {
        const updatedSatellites: Satellite[] = [];

        for (const group of satelliteGroups) {
            if (group != "geo") continue;

            const vec = Module.getSatellitesDTO(group);

            for (let i = 0; i < vec.size(); i++) {
                const sat = vec.get(i);

                updatedSatellites.push({
                    name: sat.name,
                    lat: sat.lat,
                    lon: sat.lon,
                    alt: sat.alt
                });
            }
            
            vec.delete();
        }

        setSatellites(updatedSatellites);

    }, 200);

    return () => clearInterval(interval);
  }, []);

  return (
    <div>
      <Simulation satellites={satellites} />
    </div>
  );
}

export default App
