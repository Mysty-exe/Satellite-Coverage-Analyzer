import { useCubeTexture } from "@react-three/drei";
import { useThree } from "@react-three/fiber";
import { useEffect } from "react";

function Skybox() {
  const { scene } = useThree();

  const texture = useCubeTexture(
    [
            "right.png",
            "left.png",
            "top.png",
            "bottom.png",
            "front.png",
            "back.png"
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
