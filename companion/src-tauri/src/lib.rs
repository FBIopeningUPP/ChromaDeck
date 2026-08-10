use midir::MidiInput;

#[tauri::command]
fn list_midi_ports() -> Vec<String> {
    let mut available_ports = Vec::new();
    if let Ok(midi_in) = MidiInput::new("ChromaDeck Companion Reader") {
        for port in midi_in.ports().iter() {
            if let Ok(port_name) = midi_in.port_name(port) {
                available_ports.push(port_name);
            }
        }
    }
    available_ports
}

#[cfg_attr(mobile, tauri::mobile_entry_point)]
pub fn run() {
    tauri::Builder::default()
        .plugin(tauri_plugin_opener::init())
        .invoke_handler(tauri::generate_handler![list_midi_ports])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}