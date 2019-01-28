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
        doSleepProfile3()
    }
    
    func doSleepProfile1() {
        printMessage("starting iteration (usleep)")
        let iterationCount = profileSleep_usleep()
        printMessage("iteration count (usleep): \(iterationCount)")
    }
    
    func doSleepProfile2() {
        printMessage("starting iteration (select)")
        let iterationCount = profileSleep_select()
        printMessage("iteration count (select): \(iterationCount)")
    }
    
    func doSleepProfile3() {
        printMessage("starting iteration (hard loop)")
        let iterationCount = profileSleep_hardLoop()
        printMessage("iteration count (hard loop): \(iterationCount)")
    }
    
}
