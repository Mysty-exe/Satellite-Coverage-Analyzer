import { CameraControls, FirstPersonControls, KeyboardControls, OrbitControls, useKeyboardControls } from "@react-three/drei";
import { Canvas, useFrame, useThree, type CameraProps } from "@react-three/fiber"
import { useEffect, useRef, type RefObject } from "react";
import { MathUtils, Vector3 } from "three";
import { cos } from "three/tsl";

interface SphereMeshProps {
    ref: RefObject<any>,
    position: any,
    args: any,
    color: string,
    wireframe: boolean
}

interface SceneProps {
    clicking: boolean
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
        earthRef.current.rotation.y += delta * 0.1;
    });

    return (
        <SphereMesh ref={earthRef} position={[0, 0, 0]} args={[2, 32, 32]} color={"lightblue"} wireframe={true}/>
    )
}

const SatelliteMesh = () => {
    const satelliteRef = useRef(null);

    return (
        <SphereMesh ref={satelliteRef} position={[2, 2, 0]} args={[0.3, 32, 16]} color={"red"} wireframe={true}/>
    )
}

function handleCamera(clicking: boolean) {
    const { camera } = useThree();
    const [, getKeys] = useKeyboardControls();
    const dragging = useRef(false);
    const cameraValues = useRef({ pitch: 0, yaw: 0 });
    const previous = useRef({ x: 0, y: 0 });

    useEffect(() => {
        const down = () => dragging.current = true;
        const up = () => dragging.current = false;

        window.addEventListener("pointerdown", down);
        window.addEventListener("pointerup", up);

        return () => {
            window.removeEventListener("pointerdown", down);
            window.removeEventListener("pointerup", up);
        };
    }, []);


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

        if (!dragging.current)
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
}

const Scene = (props: SceneProps) => {
    handleCamera(props.clicking);

    return (
        <>            
            <EarthMesh />
            {/* <SatelliteMesh /> */}
        </>
    )
}

function Simulation() {
    const globalClick = useRef(false);

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
            <Canvas camera={{fov: 90}} 
                onPointerDown={() => (globalClick.current = true)}
                onPointerUp={() => (globalClick.current = false)}>
                <ambientLight />
                <Scene clicking={globalClick.current} />
            </Canvas>
        </KeyboardControls>
    )
}

export default Simulation
