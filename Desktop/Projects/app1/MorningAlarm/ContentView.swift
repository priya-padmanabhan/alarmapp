import SwiftUI
import SwiftData

struct ContentView: View {
    @Environment(\.modelContext) var modelContext
    @EnvironmentObject var alarmManager: AlarmManager
    @State private var showingAddAlarm = false
    @State private var showingEditAlarm = false
    @State private var activeAlarmAlert = false

    var body: some View {
        ZStack {
            Color(red: 0.05, green: 0.05, blue: 0.08)
                .ignoresSafeArea()

            VStack(spacing: 0) {
                VStack(alignment: .leading, spacing: 8) {
                    Text("Alarms")
                        .font(.system(size: 32, weight: .bold))
                        .foregroundColor(Color(red: 0.95, green: 0.94, blue: 0.92))
                }
                .frame(maxWidth: .infinity, alignment: .leading)
                .padding(.horizontal, 20)
                .padding(.vertical, 16)

                if alarmManager.alarms.isEmpty {
                    VStack(spacing: 12) {
                        Text("No alarms yet")
                            .font(.system(size: 16, weight: .medium))
                            .foregroundColor(Color(red: 0.7, green: 0.68, blue: 0.65))
                        Text("Tap + to create your first alarm")
                            .font(.system(size: 14, weight: .regular))
                            .foregroundColor(Color(red: 0.6, green: 0.58, blue: 0.55))
                    }
                    .frame(maxWidth: .infinity, maxHeight: .infinity)
                    .background(Color(red: 0.05, green: 0.05, blue: 0.08))
                } else {
                    ScrollView {
                        VStack(spacing: 12) {
                            ForEach(alarmManager.alarms, id: \.id) { alarm in
                                AlarmRow(alarm: alarm)
                                    .contentShape(Rectangle())
                                    .onTapGesture {
                                        alarmManager.setActiveAlarm(alarm)
                                        activeAlarmAlert = true
                                    }
                            }
                        }
                        .padding(20)
                    }
                    .background(Color(red: 0.05, green: 0.05, blue: 0.08))
                }

                Spacer()

                HStack(spacing: 12) {
                    Button(action: { showingAddAlarm = true }) {
                        HStack(spacing: 8) {
                            Image(systemName: "plus")
                                .font(.system(size: 16, weight: .semibold))
                            Text("Add Alarm")
                                .font(.system(size: 16, weight: .semibold))
                        }
                        .frame(maxWidth: .infinity)
                        .padding(.vertical, 12)
                        .background(Color(red: 0.2, green: 0.25, blue: 0.3))
                        .foregroundColor(Color(red: 0.95, green: 0.94, blue: 0.92))
                        .cornerRadius(8)
                    }
                }
                .padding(20)
            }
        }
        .onAppear {
            alarmManager.setupSwiftData(modelContext: modelContext)
        }
        .sheet(isPresented: $showingAddAlarm) {
            AlarmEditorView(isPresented: $showingAddAlarm, editingAlarm: nil)
                .environmentObject(alarmManager)
        }
        .sheet(isPresented: $showingEditAlarm) {
            if let alarm = alarmManager.activeAlarm {
                AlarmEditorView(isPresented: $showingEditAlarm, editingAlarm: alarm)
                    .environmentObject(alarmManager)
            }
        }
        .alert("Alarm Details", isPresented: $activeAlarmAlert) {
            if let alarm = alarmManager.activeAlarm {
                Button("Edit", action: { showingEditAlarm = true })
                Button("Delete", role: .destructive) {
                    alarmManager.deleteAlarm(alarm)
                }
                Button("Dismiss", role: .cancel) {
                    alarmManager.dismissAlarm()
                }
            }
        } message: {
            if let alarm = alarmManager.activeAlarm {
                Text("Time: \(alarm.timeString)\nMode: \(alarm.mode.rawValue)")
            }
        }
    }
}

#Preview {
    ContentView()
        .environmentObject(AlarmManager())
        .modelContainer(for: Alarm.self, inMemory: true)
}
