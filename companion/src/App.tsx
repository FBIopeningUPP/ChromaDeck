import { useEffect, useState } from "react";
import { invoke } from "@tauri-apps/api/core";
import "./App.css";

function App() {
  const [faderLevels] = useState([85, 42, 18, 100]);
  const [deviceName, setDeviceName] = useState("SCANNING...");

  useEffect(() => {
    async function scanMidiPorts() {
      try {
        const ports = await invoke<string[]>("list_midi_ports");
        if (ports.length > 0) {
          setDeviceName(ports[0]);
        } else {
          setDeviceName("NO HARDWARE DETECTED");
        }
      } catch (error) {
        console.error("Failed to feth midi ports", error);
      }
    }

    scanMidiPorts();
    const interval = setInterval(scanMidiPorts, 2000);
    return () => clearInterval(interval);
  }, []);

  return (
    <div className="app-container">
      <div className="panel sidebar">
        <div className="brand">ChromaDeck //</div>
        <div style={{ display: 'flex', flexDirection: 'column', gap: '8px' }}>
          <div className="nav-item active">Mixer</div>
          <div className="nav-item">Routing</div>
          <div className="nav-item">Settings</div>
        </div>
      </div>

      <div className="panel main-content">
        <div className="header">
          <h2>Main Console</h2>
          <div className="status-badge" style={{color: deviceName == "NO HARDWARE DETECTED" ? '#ff3333' : 'var(--accent-secondary)' }}>
            <div className="status-dot" style={{ backgroundColor: deviceName === "NO HARDWARE DETECTED" ? '#ff3333' : 'var(--accent-secondary)' }}></div>
            {deviceName}
          </div>
        </div>

        <div className="faders-grid">
          {faderLevels.map((level, i) => (
            <div key={i} className="channel-strip">
              <div className="channel-label">CH 0{i + 1}</div>
              
              <div className="fader-track">
                <div className="fader-thumb" style={{ bottom: `calc(${level}% - 6px)` }}></div>
              </div>
              
              <div className="channel-value">{level}</div>
            </div>
          ))}
        </div>
      </div>
    </div>
  );
}

export default App;