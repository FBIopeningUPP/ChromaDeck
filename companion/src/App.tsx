import { useState } from "react";
import "./App.css";

function App() {
  const [faderLevels] = useState([85, 42, 18, 100]);

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
          <div className="status-badge">
            <div className="status-dot"></div>
            SYNC_OK
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