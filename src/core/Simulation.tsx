import Sun from "./Sunlight";
import SatelliteGroup from "../rendering/SatelliteMesh";
import EarthMesh, { earth } from "../rendering/EarthMesh";
import { OrbitControls } from "@react-three/drei";
import { useFrame } from "@react-three/fiber"
import { Suspense, useEffect, useRef, type RefObject } from "react";
import Skybox from "../rendering/Skymap";

interface SimulationProps {
    workerRef: RefObject<any>
    satellitesRef: RefObject<any>
    tSinceRef: RefObject<any>
    timeRateRef: RefObject<any>
}

const Scene = ({ satellitesRef, tSinceRef, timeRateRef, workerRef }: SimulationProps) => {
        const scene = useRef(null);

        useEffect(() => {
            if (scene.current) {
                const date = new Date();
                const utcHours =
                date.getUTCHours() +
                date.getUTCMinutes() / 60 +
                date.getUTCSeconds() / 3600;

                const longitude = (utcHours - 12) * 15;

                scene.current.rotation.y = (-180 + longitude) * Math.PI / 180;
            }
        }, []);

        useFrame((_, delta) => {
            tSinceRef.current += timeRateRef.current * delta;

            workerRef.current.postMessage({
                type: "setTimeRate",
                tSince: tSinceRef.current
            });

            workerRef.current.postMessage({
                type: "getSatellite",
                index: 150
            });

            const earthRotationSpeed = (2 * Math.PI) / (23 * 56 * 60);
            scene.current.rotation.y += delta * earthRotationSpeed * timeRateRef.current;
        });

    return (
        <>
            <group rotation={[earth.tilt * Math.PI / 180, 0, 0]}>
                <group ref={scene} rotation={[0, 0, 0]}>
                    <EarthMesh />
                    <SatelliteGroup satellitesRef={satellitesRef} />
                </group>
            </group>
        </>
    )
}

function Simulation({ satellitesRef, tSinceRef, timeRateRef, workerRef }: SimulationProps) {
    return (
        <>
            <OrbitControls minDistance={earth.radius + 2} maxDistance={600}/>
            <Sun timeRateRef={timeRateRef} />
            <ambientLight intensity={0.1} />
            <Suspense fallback={null}>
                <Skybox />
                <Scene satellitesRef={satellitesRef} tSinceRef={tSinceRef} timeRateRef={timeRateRef} workerRef={workerRef} />
            </Suspense>
        </>
    )
}

export default Simulation
