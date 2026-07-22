import type { RefObject } from "react";

interface GroupProps {
    name: string,
    types: RefObject<Map<any, any>>,
    workerRef: RefObject<any>
}

const onExpand = (name:string, types: RefObject<Map<any, any>>) => {
    let currentList = types.current.get(name);
    currentList.forEach((type: any[]) => {
      type[5] = !type[5];
    });
}

const onChange = (name:string, types: RefObject<Map<any, any>>, i: number, workerRef: RefObject<any>) => {
    let currentList = types.current.get(name);
    currentList[i][4] = !currentList[i][4];
    types.current.set(name, currentList);

    workerRef.current.postMessage({
        type: "updateGroups",
        groups: types.current
    });
}

function Group({ name, types, workerRef }: GroupProps) {

  if (!types.current) return <></>;

  return (
    <div className="category">

        <div className="category-header" style={{ color: types.current.get(name)[0][1] }}>
            <span onClick={() => onExpand(name, types)}> {types.current.get(name)[0][5] ? <>▼ {name}</> : <>▶ {name}</>}</span>
            <span className="count">{types.current.get(name)[0][2]}</span>
        </div>

        {types.current.get(name)[0][5] &&
            <div className="category-items">
                {types.current.get(name).map((type, i) => 
                    <label className="filter-item" key={i}>
                        <input type="checkbox" style={{ accentColor: type[1] }} checked={type[4]} 
                        onChange={() => onChange(name, types, i, workerRef)}/>
                        {type[0]}
                        <span>{type[3]}</span>
                    </label>
                )}
            </div>
        }

    </div>
  );
}

export default Group
