import './styles/App.css';
import Simulation from './core/Simulation.js';
import { useEffect, useRef, useState } from 'react';
import LoadingScreen from './core/LoadingScreen.js';
import { Canvas } from '@react-three/fiber';
import UI from './ui/UIOverlay.js';

type Satellite = {
    name: string;
    colour: string;
    lat: number;
    lon: number;
    alt: number;
};

function App() {
  const startAppDate = useRef(new Date());
  const [currentDate, setCurrentDate] = useState(new Date());
  const [loaded, setLoaded] = useState(false);
  const satellitesRef = useRef<Satellite[]>([]);
  const workerRef = useRef(null);
  const tSinceRef = useRef(1);
  const timeRateRef = useRef(1);
  const filterRef = useRef(new Map());

  useEffect(() => {
        const worker = new Worker(
            new URL("./database/loadData.ts", import.meta.url),
            { type: "module" }
        );

        workerRef.current = worker;

        worker.onmessage = (event) => {
            if (event.data.type == "update")
            {
                satellitesRef.current = event.data.data;
                setLoaded(true);
            }
            if (event.data.type == "getSatellite")
            {
            }
            if (event.data.type == "filter")
            {
                filterRef.current = event.data.data;
            }
        };

        worker.postMessage({
            type: "start",
            tSince: tSinceRef.current
        });

        return () => {
            worker.postMessage({
                type: "stop"
            });

            worker.terminate();
        };
    }, []);

    useEffect(() => {
    const interval = setInterval(() => {
        setCurrentDate(new Date(startAppDate.current.getTime() + (tSinceRef.current * 1000)));
        }, 200);

        return () => clearInterval(interval);
    }, []);

  if (!loaded) {
    return (
        <LoadingScreen />
    );
  }

  return (
    <div className="app">
        <Canvas camera={{ fov: 50, position: [0, 0, 300] }}>
            <Simulation satellitesRef={satellitesRef} tSinceRef={tSinceRef} timeRateRef={timeRateRef} workerRef={workerRef} />
        </Canvas>
        <UI startDate={startAppDate.current} date={currentDate} tSinceRef={tSinceRef} timeRateRef={timeRateRef} groups={filterRef} workerRef={workerRef} />
    </div>
  );
}

export default App
