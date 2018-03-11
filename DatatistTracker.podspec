#
# Be sure to run `pod lib lint DatatistTracker.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'DatatistTracker'
  s.version          = '2.1.4'
  s.summary          = ' The DatatistTracker is an Objective-C framework (iOS and OSX) for sending analytics to a Datatist server.'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
The DatatistTracker is an Objective-C framework (iOS and OSX) for sending analytics to a Datatist server.
 
 Datatist server is a downloadable, Free/Libre (GPLv3 licensed) real time web analytics software, [http://datatist.org](http://datatist.org).
 This framework implements the Datatist tracking REST API [http://datatist.org/docs/tracking-api/reference.](http://datatist.org/docs/tracking-api/reference/)
 
 ###How does it work
 
 1. Create and configure the tracker
 2. Track screen views, events, errors, social interaction, search, goals and more
 3. Let the SDK dispatch events to the Datatist server automatically, or dispatch events manually
 
 All events are persisted locally in Core Data until they are dispatched and successfully received by the Datatist server.
 
 All methods are asynchronous and will return immediately.
                       DESC

  s.homepage         = 'https://github.com/Datatist/DatatistTracker'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'commerial' }
  s.author           = { 'Datatist' => 'info@datatist.com' }
  s.source           = { :git => 'https://github.com/Datatist/DatatistTracker.git', :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.ios.deployment_target = '7.0'

  s.source_files = 'lib/include/*.h'
  s.public_header_files = 'lib/include/*.h'
  s.vendored_libraries = 'lib/*.a'
  #s.resource = 'lib/*.bundle'
  s.license      = 'COMMERCIAL'
  s.frameworks = 'UIKit', 'Foundation', 'CoreGraphics', 'CoreData'
  s.ios.library = 'c++', 'stdc++', 'z'
  s.xcconfig = { 'OTHER_LDFLAGS' => '-ObjC' }

end
