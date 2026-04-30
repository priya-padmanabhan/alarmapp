import SwiftUI
import AVFoundation

struct WakeUpView: View {
    @EnvironmentObject var alarmManager: AlarmManager
    let alarm: Alarm

    @State private var isAnimating = false
    @State private var speechSynthesizer: AVSpeechSynthesizer?

    var body: some View {
        ZStack {
            Color(red: 0.05, green: 0.05, blue: 0.08)
                .ignoresSafeArea()

            VStack(spacing: 24) {
                VStack(spacing: 16) {
                    Text("Good Morning!")
                        .font(.system(size: 28, weight: .bold))
                        .foregroundColor(Color(red: 0.95, green: 0.94, blue: 0.92))

                    if alarm.mode == .quote, let quote = alarmManager.currentQuote {
                        VStack(spacing: 12) {
                            Text("\"\(quote.content)\"")
                                .font(.system(size: 16, weight: .semibold, design: .default))
                                .italic()
                                .foregroundColor(Color(red: 0.9, green: 0.88, blue: 0.85))
                                .lineLimit(3)

                            Text("— \(quote.author)")
                                .font(.system(size: 14, weight: .regular))
                                .foregroundColor(Color(red: 0.7, green: 0.68, blue: 0.65))
                        }
                        .onAppear {
                            playQuoteAudio(quote.content)
                        }
                    } else if alarm.mode == .music {
                        VStack(spacing: 12) {
                            Image(systemName: "music.note")
                                .font(.system(size: 32, weight: .regular))
                                .foregroundColor(Color(red: 0.5, green: 0.6, blue: 0.65))
                                .scaleEffect(isAnimating ? 1.1 : 1.0)
                                .animation(.easeInOut(duration: 1).repeatForever(autoreverses: true), value: isAnimating)

                            Text(alarm.musicTitle ?? "Your Music")
                                .font(.system(size: 18, weight: .semibold))
                                .foregroundColor(Color(red: 0.95, green: 0.94, blue: 0.92))
                        }
                        .onAppear {
                            isAnimating = true
                        }
                    }
                }
                .padding(24)
                .background(Color(red: 0.1, green: 0.1, blue: 0.13))
                .cornerRadius(12)
                .padding(20)

                Spacer()

                HStack(spacing: 12) {
                    Button(action: {
                        alarmManager.snoozeAlarm()
                    }) {
                        VStack(spacing: 6) {
                            Image(systemName: "moon.zzz")
                                .font(.system(size: 18, weight: .semibold))
                            Text("Snooze")
                                .font(.system(size: 12, weight: .semibold))
                        }
                        .frame(maxWidth: .infinity)
                        .padding(.vertical, 12)
                        .background(Color(red: 0.2, green: 0.25, blue: 0.3))
                        .foregroundColor(Color(red: 0.95, green: 0.94, blue: 0.92))
                        .cornerRadius(8)
                    }

                    Button(action: {
                        alarmManager.dismissAlarm()
                    }) {
                        VStack(spacing: 6) {
                            Image(systemName: "xmark.circle.fill")
                                .font(.system(size: 18, weight: .semibold))
                            Text("Dismiss")
                                .font(.system(size: 12, weight: .semibold))
                        }
                        .frame(maxWidth: .infinity)
                        .padding(.vertical, 12)
                        .background(Color(red: 0.3, green: 0.35, blue: 0.4))
                        .foregroundColor(Color(red: 0.95, green: 0.94, blue: 0.92))
                        .cornerRadius(8)
                    }
                }
                .padding(20)
            }
        }
    }

    private func playQuoteAudio(_ quote: String) {
        let utterance = AVSpeechUtterance(string: quote)
        utterance.voice = AVSpeechSynthesisVoice(language: "en-US")
        utterance.rate = 0.5
        speechSynthesizer = AVSpeechSynthesizer()
        speechSynthesizer?.speak(utterance)
    }
}

#Preview {
    WakeUpView(alarm: Alarm(time: Date(), mode: .quote))
        .environmentObject(AlarmManager())
}
