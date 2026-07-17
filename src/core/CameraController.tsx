import { useCursor, useKeyboardControls } from "@react-three/drei";
import { useFrame, useThree } from "@react-three/fiber"
import { useEffect, useRef, useState } from "react";
import { Vector3 } from "three";

let currentZoom = 0;

interface CameraControllerProps {
    minDistance: number,
    maxDistance: number
}

const CameraController = (props: CameraControllerProps) => {
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
        const speed = delta * 10;
        const forwardDir = new Vector3();
        const rightDir = new Vector3();

        camera.getWorldDirection(forwardDir);
        rightDir.crossVectors(camera.up, forwardDir).normalize();
        let movement = new Vector3();

        if (forward) movement.add(forwardDir.multiplyScalar(speed))
        if (backward) movement.add(forwardDir.multiplyScalar(-speed))
        if (right) movement.add(rightDir.multiplyScalar(-speed))
        if (left) movement.add(rightDir.multiplyScalar(speed))
        if (up)  movement.add(new Vector3(0, 1, 0).multiplyScalar(speed))
        if (down) movement.add(new Vector3(0, -1, 0).multiplyScalar(speed))

        camera.position.add(movement.normalize().multiplyScalar(speed));
        if (camera.position.length() < props.minDistance || camera.position.length() > props.maxDistance) {
            camera.position.sub(movement.normalize().multiplyScalar(speed));
        }

        const { x, y } = state.pointer;

        const xOffset = x - previous.current.x;
        const yOffset = y - previous.current.y;

        previous.current.x = x;
        previous.current.y = y;

        if (!dragging)
            return

        cameraValues.current.yaw -= xOffset * 1.5;
        cameraValues.current.pitch += yOffset * 1.5;

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

export default CameraController
