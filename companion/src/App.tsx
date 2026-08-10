import { useState } from "react";
import "./App.css"

function App() {
  const [faderLevels] = useState([85, 42, 18, 100]);
  return (
    <div className="app-container">
      <div className="glass-panel sidebar">
        <div className="brand">ChromaDeck</div>
        <div style={{marginTop: '30px'}}>
          <div className="nav-item active">
            <span></span> Mixer
          </div>
          <div className="nav-item">
            <span></span> Hardware
          </div>
          <div className="nav-item">
            <span></span> Lighting
          </div>
        </div>
      </div>
      <div className="glass-panel main-content">
        <div className="header">
          <h2>Mixer Overview</h2>
          <div className="status-badge">
            <div className="status-dot"></div>
            Device Connected
          </div>
        </div>
        <div className="faders-grid">
          {faderLevels.map((level, i) => (
            <div key={i} style={{ display: 'flex', flexDirection: 'column', alignItems: 'center', gap: '20px',  padding: '20px'}}>
              <h3 style = {{color: 'var(--text-muted)'}}>CH {i + 1}</h3>
              <div className="fader-track">
                <div className="fader-fill" style={{ height: `${level}%` }}></div>
                <div className="fader-thumb" style={{bottom: `calc(${level}%-10px)`}}></div>
              </div>
              <div style={{ fontSize: '32px', fontWeight: '800' }}>{level}</div>
            </div>
          ))}
        </div>
      </div>
    </div>
  );
}
export default App;