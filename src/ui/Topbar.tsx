import { useRef } from "react";
import TimeControls from "./TimeControls";
import type { UIProps } from "./UIOverlay";

function Topbar(props: UIProps) {
  const showTimeMenu = useRef(false);

  return (
    <div className="topbar">
        <div className="topbar-left">
            <h2 className="logo">
                Myst Atlas
            </h2>

            <input
                className="search"
                type="text"
                placeholder="Search satellites..."
            />
        </div>

        <div className="topbar-right">
            <div className="time" onClick={() => {
              showTimeMenu.current = !showTimeMenu.current;
          }}>
                {props.date.toLocaleString()}
            </div>

          {showTimeMenu.current && <TimeControls startDate={props.startDate} date={props.date} tSinceRef={props.tSinceRef} timeRateRef={props.timeRateRef} workerRef={props.workerRef} groups={props.groups} showTime={showTimeMenu} />}
        </div>
    </div>
  );
}

export default Topbar
