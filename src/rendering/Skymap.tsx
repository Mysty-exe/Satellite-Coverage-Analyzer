import { useCubeTexture } from "@react-three/drei";
import { useThree } from "@react-three/fiber";
import { useEffect, useMemo } from "react";
import { CubeTextureLoader } from "three";

function Skybox() {
  const { scene } = useThree();

  const texture = useCubeTexture(
    [
            "right.jpg",
            "left.jpg",
            "top.jpg",
            "bottom.jpg",
            "front.jpg",
            "back.jpg"
        ],
        {
            path: "/Skybox/"
        }
  );
  
  useEffect(() => {
        scene.background = texture;

        return () => {
            scene.background = null;
        };
    }, [texture]);


  return null;
}

export default Skybox
