import Sun from "./Sunlight";
import SatelliteMesh from "../rendering/SatelliteMesh";
import EarthMesh, { earth } from "../rendering/EarthMesh";
import CameraController from "./CameraController";
import { KeyboardControls } from "@react-three/drei";
import { Canvas, useFrame } from "@react-three/fiber"
import { useEffect, useRef } from "react";
import Skybox from "../rendering/Skymap";

interface SimulationProps {
    satellites: any[]
}

const Scene = ({ satellites }: SimulationProps) => {
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

        useFrame((state, delta) => {
            if (scene.current) {
                const earthRotationSpeed = (2 * Math.PI) / (23 * 56 * 60);
                scene.current.rotation.y += delta * earthRotationSpeed;
            }
        });

    return (
        <>
            <group rotation={[earth.tilt * Math.PI / 180, 0, 0]}>
                <group ref={scene} rotation={[0, 0, 0]}>
                    <EarthMesh />
                    {satellites.map((sat, i) => <SatelliteMesh key={i} colour={sat.colour} lat={sat.lat} lon={sat.lon} alt={earth.radius + (sat.alt / 1000)} />)}
                </group>
            </group>
        </>
    )
}

function Simulation(props: SimulationProps) {
    return (
        <KeyboardControls
            map={[
                { name: "forward", keys: ["ArrowUp", "w", "W"] },
                { name: "backward", keys: ["ArrowDown", "s", "S"] },
                { name: "right", keys: ["ArrowRight", "d", "D"] },
                { name: "left", keys: ["ArrowLeft", "a", "A"] },
                { name: "up", keys: ["Space"] },
                { name: "down", keys: ["Shift"] }
            ]}>
            <Canvas camera={{ fov: 50, position: [0, 0, 25] }} >
                <Skybox />
                <Sun />
                <ambientLight intensity={0.1} />
                <CameraController minDistance={earth.radius} maxDistance={100} />
                <Scene satellites={props.satellites} />
            </Canvas>
        </KeyboardControls>
    )
}

export default Simulation
