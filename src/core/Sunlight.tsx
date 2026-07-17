import { useFrame } from "@react-three/fiber";
import { useRef } from "react";

const Sun = () => {
    const sunRef = useRef(null);

    useFrame((state, delta) => {
        const speed = (2 * Math.PI) / (365 * 24 * 60 * 60);
        const angle = state.clock.elapsedTime * speed;

        sunRef.current.position.y = 0;
        sunRef.current.position.x = -1 * Math.cos(angle);
        sunRef.current.position.z = Math.sin(angle);
    });

    return (
        <directionalLight ref={sunRef} intensity={2} />
    )
}

export default Sun
