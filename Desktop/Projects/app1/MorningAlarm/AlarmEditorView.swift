import SwiftUI

struct AlarmEditorView: View {
    @EnvironmentObject var alarmManager: AlarmManager
    @Binding var isPresented: Bool
    var editingAlarm: Alarm?

    @State private var selectedTime = Date()
    @State private var selectedMode: AlarmMode = .quote
    @State private var musicTitle = ""

    private var isEditing: Bool {
        editingAlarm != nil
    }

    var body: some View {
        ZStack {
            Color(red: 0.05, green: 0.05, blue: 0.08)
                .ignoresSafeArea()

            VStack(spacing: 20) {
                HStack {
                    Text(isEditing ? "Edit Alarm" : "New Alarm")
                        .font(.system(size: 20, weight: .bold))
                        .foregroundColor(Color(red: 0.95, green: 0.94, blue: 0.92))
                    Spacer()
                    Button(action: { isPresented = false }) {
                        Image(systemName: "xmark")
                            .font(.system(size: 16, weight: .semibold))
                            .foregroundColor(Color(red: 0.95, green: 0.94, blue: 0.92))
                    }
                }
                .padding(.horizontal, 20)
                .padding(.top, 20)
                .onAppear {
                    if let alarm = editingAlarm {
                        selectedTime = alarm.time
                        selectedMode = alarm.mode
                        musicTitle = alarm.musicTitle ?? ""
                    }
                }

                VStack(alignment: .leading, spacing: 12) {
                    Text("Time")
                        .font(.system(size: 14, weight: .semibold))
                        .foregroundColor(Color(red: 0.7, green: 0.68, blue: 0.65))

                    DatePicker("Select Time", selection: $selectedTime, displayedComponents: .hourAndMinute)
                        .datePickerStyle(.wheel)
                        .frame(height: 120)
                        .tint(Color(red: 0.5, green: 0.6, blue: 0.65))
                }
                .padding(16)
                .background(Color(red: 0.1, green: 0.1, blue: 0.13))
                .cornerRadius(8)
                .padding(.horizontal, 20)

                VStack(alignment: .leading, spacing: 12) {
                    Text("Wake-up Mode")
                        .font(.system(size: 14, weight: .semibold))
                        .foregroundColor(Color(red: 0.7, green: 0.68, blue: 0.65))

                    Picker("Mode", selection: $selectedMode) {
                        ForEach(AlarmMode.allCases, id: \.self) { mode in
                            Text(mode.rawValue).tag(mode)
                        }
                    }
                    .pickerStyle(.segmented)
                    .tint(Color(red: 0.5, green: 0.6, blue: 0.65))
                }
                .padding(.horizontal, 20)

                if selectedMode == .music {
                    VStack(alignment: .leading, spacing: 12) {
                        Text("Music Title")
                            .font(.system(size: 14, weight: .semibold))
                            .foregroundColor(Color(red: 0.7, green: 0.68, blue: 0.65))

                        TextField("e.g., Peaceful Morning", text: $musicTitle)
                            .padding(12)
                            .background(Color(red: 0.1, green: 0.1, blue: 0.13))
                            .foregroundColor(Color(red: 0.95, green: 0.94, blue: 0.92))
                            .cornerRadius(6)
                    }
                    .padding(.horizontal, 20)
                }

                Spacer()

                Button(action: saveAlarm) {
                    Text(isEditing ? "Save Alarm" : "Create Alarm")
                        .font(.system(size: 16, weight: .semibold))
                        .frame(maxWidth: .infinity)
                        .padding(.vertical, 12)
                        .background(Color(red: 0.3, green: 0.4, blue: 0.45))
                        .foregroundColor(Color(red: 0.95, green: 0.94, blue: 0.92))
                        .cornerRadius(8)
                }
                .padding(20)
            }
        }
    }

    private func saveAlarm() {
        if let alarm = editingAlarm {
            alarm.time = selectedTime
            alarm.mode = selectedMode
            alarm.musicTitle = selectedMode == .music ? musicTitle : nil
            alarmManager.updateAlarm(alarm)
        } else {
            let alarm = Alarm(
                time: selectedTime,
                isEnabled: true,
                mode: selectedMode,
                musicTitle: selectedMode == .music ? musicTitle : nil
            )
            alarmManager.addAlarm(alarm)
        }
        isPresented = false
    }
}

#Preview {
    AlarmEditorView(isPresented: .constant(true))
        .environmentObject(AlarmManager())
}
