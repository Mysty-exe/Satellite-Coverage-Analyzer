import { useEffect, useRef, useState, type RefObject } from "react";
import Group from "./Group";

const groupNames = [
  "Earth Observation", "Communication", "Navigation", "Science & Research", "Miscellaneous"
]

interface FilterProps {
  groups: RefObject<Map<any, any>>,
  workerRef: RefObject<any>;
}

const onClick = (groups, workerRef) => {
  groupNames.forEach(group => {
    let groupTypes  = groups.current.get(group);
    groupTypes.forEach((type: any[]) => {
      type[4] = true;
    });
  })

  workerRef.current.postMessage({
    type: "updateGroups",
    groups: groups.current
  });
};

function Filter({ groups, workerRef }: FilterProps) {
  const [collapsed, setCollapsed] = useState(false);

  if (!groups || !groups.current)
    return <></>

  const total = useRef(0);

  useEffect(() => {
    if (total.current == 0) {
      groupNames.forEach(group => {
        total.current += groups.current.get(group)[0][2];        
      });
    }
  }, []);

  return (
    <div className={`filter-container ${collapsed ? "collapsed" : ""}`}>
      <div className={`filter-panel`}>
          <div className="panel-header">
              <h3>Satellites</h3>

              <div className="filter-actions">
                  <button onClick={() => onClick(groups, workerRef)}>
                  Toggle All - {total.current}</button>
              </div>
          </div>

          <div className="category">

            {groupNames.map((name, i) => <Group key={i} name={name} types={groups} workerRef={workerRef}/>)}

          </div>
      </div>

    <button
        className="collapse-button"
        onClick={() => setCollapsed(!collapsed)}
      >
        {collapsed ? "❯" : "❮"}
    </button>
    </div>
  );
}

export default Filter
