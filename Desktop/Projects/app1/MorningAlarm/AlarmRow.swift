import SwiftUI

struct AlarmRow: View {
    let alarm: Alarm
    @EnvironmentObject var alarmManager: AlarmManager

    var body: some View {
        HStack(spacing: 12) {
            VStack(alignment: .leading, spacing: 4) {
                Text(alarm.timeString)
                    .font(.system(size: 18, weight: .semibold))
                    .foregroundColor(Color(red: 0.95, green: 0.94, blue: 0.92))

                HStack(spacing: 4) {
                    Image(systemName: alarm.mode == .quote ? "quote.bubble" : "music.note")
                        .font(.system(size: 12, weight: .regular))
                    Text(alarm.mode.rawValue)
                        .font(.system(size: 12, weight: .regular))
                }
                .foregroundColor(Color(red: 0.7, green: 0.68, blue: 0.65))
            }

            Spacer()

            Toggle("", isOn: Binding(
                get: { alarm.isEnabled },
                set: { newValue in
                    var updatedAlarm = alarm
                    updatedAlarm.isEnabled = newValue
                    alarmManager.updateAlarm(updatedAlarm)
                }
            ))
            .tint(Color(red: 0.5, green: 0.6, blue: 0.65))
        }
        .padding(12)
        .background(Color(red: 0.1, green: 0.1, blue: 0.13))
        .cornerRadius(8)
    }
}
