import Foundation
import SwiftData
import UserNotifications

@MainActor
class AlarmManager: ObservableObject {
    @Published var alarms: [Alarm] = []
    @Published var notificationGranted = false
    @Published var activeAlarm: Alarm?
    @Published var currentQuote: Quote?

    private var modelContext: ModelContext?
    private let quoteService = QuoteService()

    func setupSwiftData(modelContext: ModelContext) {
        self.modelContext = modelContext
        loadAlarms()
    }

    func loadAlarms() {
        guard let modelContext else { return }
        let descriptor = FetchDescriptor<Alarm>(
            sortBy: [SortDescriptor(\.time, order: .forward)]
        )
        alarms = (try? modelContext.fetch(descriptor)) ?? []
    }

    func addAlarm(_ alarm: Alarm) {
        guard let modelContext else { return }
        modelContext.insert(alarm)
        try? modelContext.save()
        loadAlarms()
        scheduleNotification(for: alarm)
    }

    func updateAlarm(_ alarm: Alarm) {
        guard let modelContext else { return }
        try? modelContext.save()
        loadAlarms()
        if alarm.isEnabled {
            scheduleNotification(for: alarm)
        } else {
            cancelNotification(for: alarm)
        }
    }

    func deleteAlarm(_ alarm: Alarm) {
        guard let modelContext else { return }
        modelContext.delete(alarm)
        try? modelContext.save()
        loadAlarms()
        cancelNotification(for: alarm)
    }

    func scheduleNotification(for alarm: Alarm) {
        guard alarm.isEnabled else { return }

        let content = UNMutableNotificationContent()
        content.title = "Time to wake up!"
        content.body = alarm.mode == .quote ? "Your daily inspiration awaits" : "Your music is ready"
        content.sound = .default
        content.badge = NSNumber(value: UIApplication.shared.applicationIconBadgeNumber + 1)
        content.userInfo = ["alarmID": alarm.id.uuidString, "mode": alarm.mode.rawValue]

        var dateComponents = Calendar.current.dateComponents([.year, .month, .day, .hour, .minute], from: alarm.time)
        dateComponents.second = 0

        if let fireDate = Calendar.current.date(from: dateComponents), fireDate <= Date() {
            dateComponents.day = (dateComponents.day ?? 1) + 1
        }

        let trigger = UNCalendarNotificationTrigger(dateMatching: dateComponents, repeats: false)
        let request = UNNotificationRequest(identifier: alarm.id.uuidString, content: content, trigger: trigger)

        UNUserNotificationCenter.current().add(request) { error in
            if let error = error {
                print("Error scheduling notification: \(error)")
            }
        }
    }

    func cancelNotification(for alarm: Alarm) {
        UNUserNotificationCenter.current().removePendingNotificationRequests(withIdentifiers: [alarm.id.uuidString])
    }

    func setActiveAlarm(_ alarm: Alarm) {
        activeAlarm = alarm
        if alarm.mode == .quote {
            Task {
                await fetchQuoteForAlarm()
            }
        }
    }

    func fetchQuoteForAlarm() async {
        do {
            currentQuote = try await quoteService.fetchQuote()
        } catch {
            print("Error fetching quote: \(error)")
        }
    }

    func dismissAlarm() {
        activeAlarm = nil
        currentQuote = nil
    }

    func snoozeAlarm(minutes: Int = 9) {
        guard let alarm = activeAlarm else { return }
        let newTime = Date().addingTimeInterval(TimeInterval(minutes * 60))
        let newAlarm = Alarm(
            time: newTime,
            isEnabled: true,
            mode: alarm.mode,
            musicTitle: alarm.musicTitle
        )
        addAlarm(newAlarm)
        dismissAlarm()
    }
}
