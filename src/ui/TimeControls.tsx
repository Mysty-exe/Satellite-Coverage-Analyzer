import { useState, type RefObject } from "react";
import type { UIProps } from "./UIOverlay";

interface TimeControlsProps {
  showTime: RefObject<boolean>;
}

function TimeControls({ startDate, date, tSinceRef, timeRateRef, workerRef, groups, showTime }: UIProps & TimeControlsProps) {
    const [quickSpeed, setQuickSpeed] = useState(1);

    const setQuickSpeedFunc = (num: number) => {
        timeRateRef.current = num;
        setQuickSpeed(num);
    }

    return (
        <div className="time-popup">

            <div className="time-header">
                <h3>Simulation Time</h3>

                <button className="close-button"
                    onClick={() => {
                        showTime.current = false;
                    }}
                >×</button>
            </div>

            <div className="current-time">
                <div className="date">{date.toLocaleDateString()}</div>
                <div className="clock">{date.toLocaleTimeString()}</div>
            </div>

            <button className="reset-button"
            onClick={() => {
                const currentTime = new Date();
                tSinceRef.current = (currentTime.getTime() - startDate.getTime()) / 1000;
            }}>
                Reset to Current Time
            </button>

            <div className="custom-section">

                <label>Custom Date & Time</label>

                <input type="datetime-local"
                    onChange={e => {
                        const selectedDate = new Date(e.target.value);
                        tSinceRef.current = (selectedDate.getTime() - startDate.getTime()) / 1000;
                    }}
                />

            </div>

            <div className="speed-section">

                <label>Time Rate</label>

                <div className="rate-input">
                    <input
                        type="number"
                        min="-10000"
                        max="10000"
                        value={timeRateRef.current}
                        onChange={e => {
                            timeRateRef.current = e.target.value;
                            setQuickSpeed(-1);
                            if (timeRateRef.current == 1 || timeRateRef.current == 10 || timeRateRef.current == 100)
                                setQuickSpeed(timeRateRef.current);
                        }}
                    />

                    <span className="rate-unit">×</span>
                </div>

            </div>

            <div className="speed-section">

                <label>Quick Speed</label>

                <div className="speed-options">

                    <button className={(quickSpeed == 1) ? "active" : ""}
                        onClick={() => setQuickSpeedFunc(1)}
                    >1x</button>
                    <button className={(quickSpeed == 10) ? "active" : ""}
                        onClick={() => setQuickSpeedFunc(10)}
                    >10x</button>
                    <button className={(quickSpeed == 100) ? "active" : ""}
                        onClick={() => setQuickSpeedFunc(100)}
                    >100x</button>

                </div>

            </div>
        </div>
    );
}

export default TimeControls;