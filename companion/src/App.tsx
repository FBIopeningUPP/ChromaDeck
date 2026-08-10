import { useEffect, useState, useRef } from "react";
import { invoke } from "@tauri-apps/api/core";
import "./App.css";

function App() {
  const [activeTab, setActiveTab] = useState("Mixer");
  
  const [faderLevels, setFaderLevels] = useState([85, 42, 18, 100]);
  const [knobLevels] = useState([0, 25, 50, 75, 100, 127]);
  const [buttonStates, setButtonStates] = useState(Array(8).fill(false));
  const [deviceName, setDeviceName] = useState("SCANNING...");
  
  const trackRefs = useRef<(HTMLDivElement | null)[]>([]);

  const handleDrag = (index: number, e: React.PointerEvent<HTMLDivElement>) => {
    const track = trackRefs.current[index];
    if (!track) return;
    
    (e.target as HTMLElement).setPointerCapture(e.pointerId);

    const updateLevel = (clientY: number) => {
      const rect = track.getBoundingClientRect();
      let newLevel = ((rect.bottom - clientY) / rect.height) * 100;
      newLevel = Math.max(0, Math.min(100, Math.round(newLevel)));
      
      setFaderLevels(prev => {
        const next = [...prev];
        next[index] = newLevel;
        return next;
      });
    };

    updateLevel(e.clientY);

    const onPointerMove = (moveEvent: PointerEvent) => updateLevel(moveEvent.clientY);
    
    const onPointerUp = (upEvent: PointerEvent) => {
      window.removeEventListener("pointermove", onPointerMove);
      window.removeEventListener("pointerup", onPointerUp);
      (e.target as HTMLElement).releasePointerCapture(upEvent.pointerId);
    };

    window.addEventListener("pointermove", onPointerMove);
    window.addEventListener("pointerup", onPointerUp);
  };

  const toggleButton = (index: number) => {
    setButtonStates(prev => {
      const next = [...prev];
      next[index] = !next[index];
      return next;
    });
  };

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
        console.error(error);
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
          <div 
            className={`nav-item ${activeTab === "Mixer" ? "active" : ""}`}
            onClick={() => setActiveTab("Mixer")}
          >
            Mixer
          </div>
          <div 
            className={`nav-item ${activeTab === "Routing" ? "active" : ""}`}
            onClick={() => setActiveTab("Routing")}
          >
            Routing
          </div>
          <div 
            className={`nav-item ${activeTab === "Settings" ? "active" : ""}`}
            onClick={() => setActiveTab("Settings")}
          >
            Settings
          </div>
        </div>
      </div>

      <div className="panel main-content">
        <div className="header">
          <h2>{activeTab.toUpperCase()}</h2>
          <div className="status-badge" style={{color: deviceName === "NO HARDWARE DETECTED" ? '#ff3333' : 'var(--accent-secondary)' }}>
            <div className="status-dot" style={{ backgroundColor: deviceName === "NO HARDWARE DETECTED" ? '#ff3333' : 'var(--accent-secondary)' }}></div>
            {deviceName}
          </div>
        </div>

        {activeTab === "Mixer" && (
          <div className="hardware-section">
            <div className="knobs-grid">
              {knobLevels.map((level, i) => (
                <div key={`knob-${i}`} className="knob-container">
                  <div className="channel-label">ENC 0{i + 1}</div>
                  <div className="knob-outer">
                    <div className="knob-inner" style={{ transform: `rotate(${(level / 127) * 270 - 135}deg)` }}>
                      <div className="knob-indicator"></div>
                    </div>
                  </div>
                  <div className="channel-value" style={{marginTop: '8px'}}>{level}</div>
                </div>
              ))}
            </div>

            <div className="buttons-grid">
              {buttonStates.map((state, i) => (
                <div 
                  key={`btn-${i}`} 
                  className={`push-button ${state ? 'active' : ''}`}
                  onPointerDown={() => toggleButton(i)}
                >
                  SW0{i + 1}
                </div>
              ))}
            </div>

            <div className="faders-grid">
              {faderLevels.map((level, i) => (
                <div key={`fader-${i}`} className="channel-strip">
                  <div className="channel-label">CH 0{i + 1}</div>
                  <div className="fader-track" ref={(el) => { trackRefs.current[i] = el; }}>
                    <div className="fader-thumb" style={{ bottom: `calc(${level}% - 6px)` }} onPointerDown={(e) => handleDrag(i, e)}></div>
                  </div>
                  <div className="channel-value">{level}</div>
                </div>
              ))}
            </div>
          </div>
        )}

        {activeTab === "Routing" && (
          <div style={{ display: 'flex', flexDirection: 'column', gap: '16px' }}>
            <div style={{ padding: '16px', background: 'var(--bg-base)', border: '1px solid var(--border-color)', borderRadius: '4px' }}>
              <div style={{ fontFamily: "'JetBrains Mono', monospace", color: 'var(--text-dim)', marginBottom: '16px' }}>MIDI CC ASSIGNMENTS</div>
              <div style={{ display: 'grid', gridTemplateColumns: '1fr 1fr', gap: '8px', fontFamily: "'JetBrains Mono', monospace", fontSize: '14px' }}>
                <div>Fader 1 -{">"} CC 01 (Modulation)</div>
                <div>Encoder 1 -{">"} CC 10 (Pan)</div>
                <div>Fader 2 -{">"} CC 07 (Volume)</div>
                <div>Encoder 2 -{">"} CC 11 (Expression)</div>
                <div>Fader 3 -{">"} CC 12 (Effect 1)</div>
                <div>Encoder 3 -{">"} CC 13 (Effect 2)</div>
                <div>Fader 4 -{">"} CC 14 (Effect 3)</div>
                <div>Encoder 4 -{">"} CC 15 (Effect 4)</div>
              </div>
            </div>
          </div>
        )}

        {activeTab === "Settings" && (
          <div style={{ display: 'flex', flexDirection: 'column', gap: '16px' }}>
            <div style={{ padding: '16px', background: 'var(--bg-base)', border: '1px solid var(--border-color)', borderRadius: '4px' }}>
              <div style={{ fontFamily: "'JetBrains Mono', monospace", color: 'var(--text-dim)', marginBottom: '16px' }}>DEVICE INFORMATION</div>
              <div style={{ display: 'flex', flexDirection: 'column', gap: '8px', fontFamily: "'JetBrains Mono', monospace", fontSize: '14px' }}>
                <div>FIRMWARE VERSION: v1.0.4 (Latest)</div>
                <div>MCU: STM32F407VG @ 168MHz</div>
                <div>DISPLAY: 4.0" ILI9488 FSMC</div>
              </div>
            </div>
          </div>
        )}
      </div>
    </div>
  );
}

export default App;