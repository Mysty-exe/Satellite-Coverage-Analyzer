import { KeyboardControls, useCursor, useKeyboardControls } from "@react-three/drei";
import { Canvas, useFrame, useThree } from "@react-three/fiber"
import { useEffect, useMemo, useRef, useState, type RefObject } from "react";
import { Vector3 } from "three";

interface SimulationProps {
    satellites: any[]
}

interface SatelliteMeshProps {
    lat: number,
    lon: number,
    alt: number
}

interface SphereMeshProps {
    ref: RefObject<any>,
    position: any,
    args: any,
    color: string,
    wireframe: boolean
}

let currentZoom = 0;
const earth = {
    pos: new Vector3(),
    radius: 2,
    tilt: 23.44
}

const SphereMesh = (props: SphereMeshProps) => {
    return (
        <mesh ref={props.ref} position={props.position}>
        <sphereGeometry args={props.args} />
        <meshStandardMaterial color={props.color}
        wireframe={props.wireframe} />
        </mesh>
    )
};

const EarthMesh = () => {
    const earthRef = useRef<any>(null);

    useFrame((state, delta, frame) => {
        // earthRef.current.rotation.y += delta * 0.02;
    });

    return (
        <SphereMesh ref={earthRef} position={earth.pos} args={[earth.radius, 32, 32]} color={"lightblue"} wireframe={true}/>
    )
}

const SatelliteMesh = ({ lat, lon, alt }: SatelliteMeshProps) => {
    const satelliteRef = useRef(null);

    const pos = useMemo(() => {
        const r = earth.radius + alt;

        return new Vector3(
            r * Math.cos(lat) * Math.cos(-lon),
            r * Math.sin(lat),
            r * Math.cos(lat) * Math.sin(-lon)
    );
    }, [lat, lon, alt]);

    return (
        <SphereMesh ref={satelliteRef} position={pos} args={[0.05, 32, 16]} color={"red"} wireframe={true}/>
    )
}

const CameraController = () => 
{
    const { camera } = useThree();
    const [, getKeys] = useKeyboardControls();
    const [dragging, setDragging] = useState(false)
    const cameraValues = useRef({ pitch: 0, yaw: 0 });
    const previous = useRef({ x: 0, y: 0 });

    useEffect(() => {
        const down = () => {
            setDragging(true);
        };
        const up = () => {
            setDragging(false);
        }
        const zoom = (e: WheelEvent) => {
            const direction = camera.getWorldDirection(new Vector3());

            currentZoom += e.deltaY * 0.01;
            currentZoom = (currentZoom < -5) ? -5 : currentZoom;
            currentZoom = (currentZoom > 5) ? 5 : currentZoom;

            if (Math.abs(currentZoom) > 4.9) return;
            camera.position.addScaledVector(direction, e.deltaY * 0.01);
        }

        window.addEventListener("pointerdown", down);
        window.addEventListener("pointerup", up);
        window.addEventListener("wheel", zoom);

        return () => {
            window.removeEventListener("pointerdown", down);
            window.removeEventListener("pointerup", up);
            window.removeEventListener("wheel", zoom);
        };
    }, []);

    useCursor(dragging, 'none', 'auto');

    useFrame((state, delta) => {
        const { forward, backward, left, right, up, down } = getKeys();
        const speed = delta * 3;
        const forwardDir = new Vector3();
        const rightDir = new Vector3();

        camera.getWorldDirection(forwardDir);
        rightDir.crossVectors(camera.up, forwardDir).normalize();
    
        if (forward) camera.position.add(forwardDir.multiplyScalar(speed));
        if (backward) camera.position.sub(forwardDir.multiplyScalar(speed))
        if (right) camera.position.sub(rightDir.multiplyScalar(speed))
        if (left) camera.position.add(rightDir.multiplyScalar(speed))
        if (up) camera.position.add(new Vector3(0, 1, 0).multiplyScalar(speed))
        if (down) camera.position.sub(new Vector3(0, 1, 0).multiplyScalar(speed))

        const { x, y } = state.pointer

        const xOffset = x - previous.current.x;
        const yOffset = y - previous.current.y;

        previous.current.x = x;
        previous.current.y = y;

        if (!dragging)
            return

        cameraValues.current.yaw -= xOffset * 1;
        cameraValues.current.pitch += yOffset * 1;

        cameraValues.current.pitch = Math.max(
            -Math.PI / 2 + 0.01,
            Math.min(Math.PI / 2 - 0.01, cameraValues.current.pitch)
        )

        camera.rotation.order = "YXZ";
        camera.rotation.y = cameraValues.current.yaw;
        camera.rotation.x = cameraValues.current.pitch;
    })

    return <></>
}

const Scene = ({ satellites }: SimulationProps) => {
    return (
        <>
            <group rotation={[earth.tilt * Math.PI / 180, -90 * Math.PI / 180, 0]}>
                <EarthMesh />
                {/* <SatelliteMesh lat={0} lon={0} alt={0} /> */}
                {satellites.map( (sat, i) => <SatelliteMesh key={i} lat={sat.lat} lon={sat.lon} alt={sat.alt / 500} /> )}
            </group>
        </>
    )
}

function Simulation(props: SimulationProps) {
    // console.log(props.satellites)

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
            <Canvas camera={{fov: 90}} >
                <ambientLight />
                <CameraController />
                <Scene satellites={props.satellites} />
            </Canvas>
        </KeyboardControls>
    )
}

export default Simulation
