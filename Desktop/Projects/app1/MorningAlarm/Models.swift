import Foundation
import SwiftData

enum AlarmMode: String, Codable, CaseIterable {
    case quote = "Quote"
    case music = "Music"
}

@Model
final class Alarm {
    var id: UUID = UUID()
    var time: Date
    var isEnabled: Bool
    var mode: AlarmMode
    var musicTitle: String? // For music mode
    var createdAt: Date = Date()

    init(time: Date, isEnabled: Bool = true, mode: AlarmMode = .quote, musicTitle: String? = nil) {
        self.time = time
        self.isEnabled = isEnabled
        self.mode = mode
        self.musicTitle = musicTitle
    }

    var timeString: String {
        let formatter = DateFormatter()
        formatter.timeStyle = .short
        return formatter.string(from: time)
    }
}
