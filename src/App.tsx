import './styles/App.css';
import Simulation from './core/Simulation.js';
import { Suspense, useEffect, useRef, useState } from 'react';
// @ts-ignore
import createModule from './wasm/SatelliteCoverage.js';
import LoadingScreen from './core/LoadingScreen.js';
import { Canvas } from '@react-three/fiber';
import { useProgress } from '@react-three/drei';

type Satellite = {
    name: string;
    colour: string;
    lat: number;
    lon: number;
    alt: number;
};

const Module = await createModule();

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
  const [loaded, setLoaded] = useState(false);
  const satellitesRef = useRef<Satellite[]>([]);
  const workerRef = useRef(null);
  const tSinceRef = useRef(1);
  const timeRateRef = useRef(1);

  useEffect(() => {
        const worker = new Worker(
            new URL("./database/loadData.ts", import.meta.url),
            { type: "module" }
        );

        workerRef.current = worker;

        worker.onmessage = (event) => {
            satellitesRef.current = event.data;
            setLoaded(true);
        };

        worker.postMessage({
            type: "start",
            groups: satelliteGroups,
            tSince: tSinceRef.current
        });

        return () => {
            worker.postMessage({
                type: "stop"
            });

            worker.terminate();
        };
    }, []);

  if (!loaded) {
    return (
        <LoadingScreen />
    );
  }

  return (
    <Canvas camera={{ fov: 50, position: [0, 0, 40] }}>
        <Simulation satellitesRef={satellitesRef} tSinceRef={tSinceRef} timeRateRef={timeRateRef} workerRef={workerRef} />
    </Canvas>
  );
}

export default App
