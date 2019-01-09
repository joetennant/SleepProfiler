import Foundation

printMessage("Running")

var runner = PeriodicRunner()
runner.runPeriodically()
RunLoop.current.run()
