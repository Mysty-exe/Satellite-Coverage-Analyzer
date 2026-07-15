import './styles/App.css';
import './styles/Loading.css';
import Simulation from './core/Simulation.js';
import { useEffect, useState } from 'react';
import { loadTLE, getTLE } from './database/db.js';
// @ts-ignore
import createModule from './wasm/SatelliteCoverage.js';

const Module = await createModule();

type Satellite = {
    name: string;
    colour: string;
    lat: number;
    lon: number;
    alt: number;
};

function getGroups() {
  const arr = Module.getSatelliteGroups();
  const groups: string[] = [];
  for (let i = 0; i < arr.size(); i++) {
    groups.push(arr.get(i));
  }
  arr.delete();

  return groups;
}


function App() {
  const satelliteGroups = getGroups();
  const [initialized, setInitialized] = useState(false);
  const [satellites, setSatellites] = useState<Satellite[]>([]);

  useEffect(() => {
    async function load() {
        for (const group of satelliteGroups) {
            await loadTLE(group);
            const data = await getTLE(group);
            Module.initializeSatelliteGroup(group, data);
        }

        setInitialized(true);
    }

    load();
  }, []);

  useEffect(() => {
    if (!initialized) return
    const interval = setInterval(() => {
        const updatedSatellites: Satellite[] = [];

        for (const group of satelliteGroups) {
            if (group != "geo") continue;

            const vec = Module.getSatellitesDTO(group);

            for (let i = 0; i < vec.size(); i++) {
                const sat = vec.get(i);

                updatedSatellites.push({
                    name: sat.name,
                    colour: sat.colour,
                    lat: sat.lat,
                    lon: sat.lon,
                    alt: sat.alt
                });
            }
            
            vec.delete();
        }

        setSatellites(updatedSatellites);

    }, 500);

    return () => clearInterval(interval);
  }, [initialized]);

  if (!initialized) {
    return (
        <div className="loader">Loading...</div>
    )
  }

  return (
    <div>
      <Simulation satellites={satellites} />
    </div>
  );
}

export default App
