import { useRef, type RefObject } from "react";
import Filter from "./Filter";
import Topbar from "./Topbar";

export interface UIProps {
  startDate: Date
  date: Date
  tSinceRef: RefObject<any>
  timeRateRef: RefObject<any>
  groups: RefObject<Map<any, any>>
  workerRef: RefObject<any>;
}

function UI(props: UIProps) {
  return (
    <div className="overlay">
      <Topbar startDate={props.startDate} date={props.date} tSinceRef={props.tSinceRef} timeRateRef={props.timeRateRef} groups={props.groups} workerRef={props.workerRef} />
      <Filter groups={props.groups} workerRef={props.workerRef} />
    </div>
  );
}

export default UI
