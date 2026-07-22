import { Instance, Instances } from "@react-three/drei";
import { useEffect, useLayoutEffect, useMemo, useRef, useState, type RefObject } from "react";
import { BackSide, Color, InstancedMesh, Matrix4, Mesh, Object3D, Vector3 } from "three";
import { earth } from "./EarthMesh";
import { useFrame, useThree } from "@react-three/fiber";

interface SatelliteMeshProps {
    satellitesRef: RefObject<any>,
}

const getPosition = (lat: number, lon: number, alt: number) => {
    const start = earth.radius + (alt / 150);

    return new Vector3(
        start * Math.cos(lat) * Math.cos(-lon),
        start * Math.sin(lat),
        start * Math.cos(lat) * Math.sin(-lon)
    );
}

const SatelliteGroup = ({ satellitesRef }: SatelliteMeshProps) => {
    const { camera } = useThree();
    const hoveredSats = useRef([]);
    const meshRef = useRef<InstancedMesh>(null);
    const hoverMesh = useRef<Mesh>(null!);
    const dummy = new Object3D();

    useFrame((state, delta) => {
        if (!meshRef.current) return;

        const satellites = satellitesRef.current;
        meshRef.current.count = satellites.length;

        let closest = hoveredSats.current[0];
        let closestDist = Infinity;

        for (const i of hoveredSats.current) {
            const sat = satellites[i];

            const dist = camera.position.distanceTo(
                getPosition(sat.lat, sat.lon, sat.alt)
            );

            if (dist < closestDist) {
                closestDist = dist;
                closest = i;
                    
            }
        }

        let hovered: number[] = [];
        hoveredSats.current.map((sat) => {
            const s = satellites[sat];
            if (camera.position.distanceTo(getPosition(s.lat, s.lon, s.alt)) == closestDist)
                hovered.push(sat);
        });
        
        satellites.forEach((sat, i) => {
            const pos = getPosition(
                sat.lat,
                sat.lon,
                sat.alt
            );

            dummy.position.copy(pos);
            dummy.updateMatrix();

            meshRef.current!.setMatrixAt(i, dummy.matrix);
            meshRef.current!.setColorAt(i, new Color(sat.colour));

            if (hovered.length == 0) {
                hoverMesh.current.visible = false;
            } else {
                hoverMesh.current.visible = true;
            }

            if (hovered.includes(i)) {
                hoverMesh.current.position.copy(
                    getPosition(sat.lat, sat.lon, sat.alt)
                );
            }
        });

        meshRef.current.instanceMatrix.needsUpdate = true;

        if (meshRef.current.instanceColor) {
            meshRef.current.instanceColor.needsUpdate = true;
        }
    });

    return (
        <>
        <instancedMesh ref={meshRef} 
        onPointerOver={(e) => {
            hoveredSats.current.push(e.instanceId);
        }}
        onPointerOut={(e) => {
            hoveredSats.current = hoveredSats.current.filter(item => item !== e.instanceId);
        }}
        args={[undefined, undefined, 20000]}>
            <sphereGeometry args={[0.5, 8, 8]} />
            <meshBasicMaterial />
        </instancedMesh>
        <mesh ref={hoverMesh}>
            <sphereGeometry args={[0.75, 8, 8]} />
            <meshBasicMaterial
                color="white"
                side={BackSide}
            />
        </mesh>
        </>
    );
}

export default SatelliteGroup
