import { useGLTF } from "@react-three/drei";
import { Box3, Sphere, Vector3 } from "three";

export const earth = {
    pos: new Vector3(),
    radius: 2,
    tilt: 23.44
}

const EarthMesh = () => {
    const { scene } = useGLTF('/Models/Earth 2/scene.gltf');
    const box = new Box3().setFromObject(scene);
    const sphere = new Sphere();
    box.getBoundingSphere(sphere);
    earth.radius = 5;

    return <primitive object={scene} scale={[0.05, 0.05, 0.05]} />;
}

export default EarthMesh