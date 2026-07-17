import { Instance, Instances } from "@react-three/drei";
import { useEffect, useLayoutEffect, useMemo, useRef, type RefObject } from "react";
import { Color, InstancedMesh, Matrix4, Object3D, Vector3 } from "three";
import { earth } from "./EarthMesh";
import { useFrame } from "@react-three/fiber";

interface SatelliteMeshProps {
    satellitesRef: RefObject<any>,
}

const getPosition = (lat: number, lon: number, alt: number) => {
    const start = earth.radius + (alt / 1000);

    return new Vector3(
        start * Math.cos(lat) * Math.cos(-lon),
        start * Math.sin(lat),
        start * Math.cos(lat) * Math.sin(-lon)
    );
}

const SatelliteGroup = ({ satellitesRef }: SatelliteMeshProps) => {
    const meshRef = useRef<InstancedMesh>(null);
    const dummy = new Object3D();
    const matrix = new Matrix4();

    useFrame((state, delta) => {
        if (!meshRef.current) return;

        const satellites = satellitesRef.current;
        meshRef.current.count = satellites.length;

        satellites.forEach((sat, i) => {
            const pos = getPosition(
                sat.lat,
                sat.lon,
                sat.alt
            );

            dummy.position.copy(pos);
            dummy.updateMatrix();

            meshRef.current!.setMatrixAt(i, dummy.matrix);
            meshRef.current!.setColorAt(
                i,
                new Color(sat.colour)
            );
        });

        meshRef.current.instanceMatrix.needsUpdate = true;

        if (meshRef.current.instanceColor)
            meshRef.current.instanceColor.needsUpdate = true;
    }, []);

    return (
        <instancedMesh ref={meshRef} args={[undefined, undefined, 20000]}>
            <sphereGeometry args={[0.1, 8, 8]} />
            <meshBasicMaterial />
        </instancedMesh>
    );
}

export default SatelliteGroup
