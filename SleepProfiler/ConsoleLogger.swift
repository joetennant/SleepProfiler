import Foundation
import os.log

struct Log {
    static var general = OSLog(subsystem: "com.sevensignal.sleepprofiler", category: "general")
}

func printMessage(_ message: Any) {
    if let messageString = message as? String {
        print(messageString)
//        print("%{public}s", log: Log.general, type: .default, messageString)
    } else {
        print(message)
//        print("%{public}@", log: Log.general, type: .default, message as! NSObject)
    }
}
