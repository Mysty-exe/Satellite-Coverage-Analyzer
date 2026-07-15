import { useMemo, useRef } from "react";
import { Vector3 } from "three";

interface SatelliteMeshProps {
    colour: string,
    lat: number,
    lon: number,
    alt: number
}

const SatelliteMesh = ({ colour, lat, lon, alt }: SatelliteMeshProps) => {
    const satelliteRef = useRef(null);

    const pos = useMemo(() => {
        const r = alt;

        return new Vector3(
            r * Math.cos(lat) * Math.cos(-lon),
            r * Math.sin(lat),
            r * Math.cos(lat) * Math.sin(-lon)
        );
    }, [lat, lon, alt]);

    return (
        <mesh ref={satelliteRef} position={pos}>
            <sphereGeometry args={[0.1, 32, 16]} />
            <meshBasicMaterial color={colour} />
        </mesh>
    )
}

export default SatelliteMesh
