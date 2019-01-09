import Foundation
import os.log

struct Log {
    static var general = OSLog(subsystem: "com.sevensignal.sleepprofiler", category: "general")
}

func printMessage(_ message: Any) {
    if let messageString = message as? String {
        os_log("%{public}s", log: Log.general, type: .default, messageString)
    } else {
        os_log("%{public}@", log: Log.general, type: .default, message as! NSObject)
    }
}
