import Foundation

struct Quote: Codable {
    let content: String
    let author: String

    enum CodingKeys: String, CodingKey {
        case content = "q"
        case author = "a"
    }
}

actor QuoteService {
    private let baseURL = "https://zenquotes.io/api/random"

    func fetchQuote() async throws -> Quote {
        guard let url = URL(string: baseURL) else {
            throw URLError(.badURL)
        }

        let (data, _) = try await URLSession.shared.data(from: url)
        let quotes = try JSONDecoder().decode([Quote].self, from: data)

        guard let quote = quotes.first else {
            throw URLError(.badServerResponse)
        }

        return quote
    }
}
