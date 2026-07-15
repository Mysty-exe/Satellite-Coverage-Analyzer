import { useThree } from "@react-three/fiber";
import { useEffect } from "react";
import { CubeTextureLoader } from "three";

function Skybox() {
  const { scene } = useThree();
  
  useEffect(() => {
    const loader = new CubeTextureLoader();
    const texture = loader.load([
      '/Skybox/right.png', '/Skybox/left.png',
      '/Skybox/top.png', '/Skybox/bottom.png',
      '/Skybox/front.png', '/Skybox/back.png'
    ]);
    
    scene.background = texture;
  }, [scene]);

  return null;
}

export default Skybox
