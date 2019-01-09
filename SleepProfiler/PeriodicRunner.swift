import Foundation

class PeriodicRunner {
    
    func runPeriodically() {
        Timer.scheduledTimer(timeInterval: 10.0,
                             target: self,
                             selector: #selector(doSleepProfiles),
                             userInfo: nil,
                             repeats: true)
    }
    @objc func doSleepProfiles() {
        doSleepProfile1()
        doSleepProfile2()
    }
    
    func doSleepProfile1() {
        printMessage("starting iteration (sleep 1)")
        let iterationCount = profileSleep1()
        printMessage("iteration count (sleep 1): \(iterationCount)")
    }
    
    func doSleepProfile2() {
        printMessage("starting iteration (sleep 2)")
        let iterationCount = profileSleep2()
        printMessage("iteration count (sleep 2): \(iterationCount)")
    }
    
}
