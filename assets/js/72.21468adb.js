(window.webpackJsonp=window.webpackJsonp||[]).push([[72],{108:function(t,s,a){"use strict";a.r(s);var e=a(0),n=Object(e.a)({},function(){var t=this,s=t.$createElement,a=t._self._c||s;return a("ContentSlotsDistributor",{attrs:{"slot-key":t.$parent.slotKey}},[a("h1",{attrs:{id:"Setup"}},[a("a",{staticClass:"header-anchor",attrs:{href:"#Setup","aria-hidden":"true"}},[t._v("#")]),t._v(" Setup")]),t._v(" "),a("h2",{attrs:{id:"Install"}},[a("a",{staticClass:"header-anchor",attrs:{href:"#Install","aria-hidden":"true"}},[t._v("#")]),t._v(" Install")]),t._v(" "),a("p",[t._v("The source is available here:")]),t._v(" "),a("ul",[a("li",[a("a",{attrs:{href:"https://github.com/rpav/cpp-pipedream",target:"_blank",rel:"noopener noreferrer"}},[t._v("https://github.com/rpav/cpp-pipedream"),a("OutboundLink")],1)])]),t._v(" "),a("p",[t._v("This is a header-only library; building by default will build examples.\nInstallation is also useful.")]),t._v(" "),a("div",{staticClass:"language-sh extra-class"},[a("pre",{pre:!0,attrs:{class:"language-sh"}},[a("code",[t._v("$ "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("git")]),t._v(" clone https://github.com/rpav/cpp-pipedream.git\n$ "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("cd")]),t._v(" cpp-pipedream\n$ "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("mkdir")]),t._v(" build"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("cd")]),t._v(" build\n$ cmake "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("..")]),t._v("\n$ "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("make")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("install")]),t._v("\n")])])]),a("p",[t._v("Additionally, tests and docs are possible, if Doxygen or "),a("code",[t._v("BUILD_TESTING")]),t._v(" is\nenabled in CMake.")]),t._v(" "),a("h2",{attrs:{id:"Examples-and-Tests"}},[a("a",{staticClass:"header-anchor",attrs:{href:"#Examples-and-Tests","aria-hidden":"true"}},[t._v("#")]),t._v(" Examples and Tests")]),t._v(" "),a("p",[t._v("Many of the examples in this documentation are available in the "),a("code",[t._v("examples/")]),t._v(" directory.  These will build by default.")]),t._v(" "),a("p",[t._v("Tests will not build by default, but you can enable them with "),a("code",[t._v("-DBUILD_TESTING=ON")]),t._v(" as appropriate to cmake, and run with "),a("code",[t._v("ctest")]),t._v(" or "),a("code",[t._v("make test")]),t._v(" etc.  Tests are in "),a("code",[t._v("t/")]),t._v(".")]),t._v(" "),a("h2",{attrs:{id:"Project-Inclusion"}},[a("a",{staticClass:"header-anchor",attrs:{href:"#Project-Inclusion","aria-hidden":"true"}},[t._v("#")]),t._v(" Project Inclusion")]),t._v(" "),a("p",[t._v("If you use cmake, and ran "),a("code",[t._v("make install")]),t._v(" (or equivalent) you should be\nable to simply pull in "),a("code",[t._v("pipedream")]),t._v(" and use it.")]),t._v(" "),a("p",[t._v("From "),a("code",[t._v("examples/CMakeLists.txt")]),t._v(":")]),t._v(" "),a("div",{staticClass:"language-cmake extra-class"},[a("pre",{pre:!0,attrs:{class:"language-cmake"}},[a("code",[a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("cmake_minimum_required")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token property"}},[t._v("VERSION")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token number"}},[t._v("3.11")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v("\n"),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("project")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),t._v("pipedream_examples"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v("\n\n"),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("set")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token variable"}},[t._v("CMAKE_CXX_STANDARD")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token number"}},[t._v("17")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v("\n\n"),a("span",{pre:!0,attrs:{class:"token comment"}},[t._v("#find_package(pipedream REQUIRED)")]),t._v("\n\n"),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("add_executable")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),t._v("setup_example setup_example.cpp"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v("\n"),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("target_link_libraries")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),t._v("setup_example\n    "),a("span",{pre:!0,attrs:{class:"token namespace"}},[t._v("PRIVATE")]),t._v(" pipedream"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v("\n\n")])])]),a("p",[t._v("From "),a("code",[t._v("examples/setup_example.cpp")]),t._v(":")]),t._v(" "),a("div",{staticClass:"language-cpp extra-class"},[a("pre",{pre:!0,attrs:{class:"language-cpp"}},[a("code",[a("span",{pre:!0,attrs:{class:"token macro property"}},[t._v("#"),a("span",{pre:!0,attrs:{class:"token directive keyword"}},[t._v("include")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token string"}},[t._v("<iostream>")])]),t._v("\n"),a("span",{pre:!0,attrs:{class:"token macro property"}},[t._v("#"),a("span",{pre:!0,attrs:{class:"token directive keyword"}},[t._v("include")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token string"}},[t._v("<piped.hpp>")])]),t._v("\n\n"),a("span",{pre:!0,attrs:{class:"token comment"}},[t._v("//using namespace piped;              // Useful, or you can alias")]),t._v("\n"),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("namespace")]),t._v(" pd "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("=")]),t._v(" piped"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n"),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("using")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("namespace")]),t._v(" piped"),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("::")]),t._v("operators"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n\n"),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("int")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("main")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("{")]),t._v("\n    "),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("auto")]),t._v(" g "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("=")]),t._v(" pd"),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("::")]),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("from_to")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token number"}},[t._v("1")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(",")]),a("span",{pre:!0,attrs:{class:"token number"}},[t._v("10")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("|")]),t._v(" pd"),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("::")]),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("filter")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("[")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("]")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("auto")]),t._v(" i"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("{")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("return")]),t._v(" i "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("%")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token number"}},[t._v("2")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("}")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n\n    "),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("for")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("auto")]),t._v(" i "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v(":")]),t._v(" g"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v("\n        std"),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("::")]),t._v("cout "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("<<")]),t._v(" i "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("<<")]),t._v(" std"),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("::")]),t._v("endl"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("}")]),t._v("\n")])])]),a("p",[t._v("Building and running this should produce the expected results:")]),t._v(" "),a("div",{staticClass:"language-sh extra-class"},[a("pre",{pre:!0,attrs:{class:"language-sh"}},[a("code",[t._v("$ "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("cd")]),t._v(" examples\n$ "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("mkdir")]),t._v(" build"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("cd")]),t._v(" build\n$ cmake "),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("..")]),t._v("\n  "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("<")]),t._v("output"),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v(">")]),t._v("\n$ "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("make")]),t._v(" setup_example\n  "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("<")]),t._v("output"),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v(">")]),t._v("\n$ ./setup_example\n1\n3\n5\n7\n9\n$\n")])])]),a("h2",{attrs:{id:"On-Headers"}},[a("a",{staticClass:"header-anchor",attrs:{href:"#On-Headers","aria-hidden":"true"}},[t._v("#")]),t._v(" On Headers")]),t._v(" "),a("p",[t._v('To get everything from pipedream ("piped" for short):')]),t._v(" "),a("div",{staticClass:"language-cpp extra-class"},[a("pre",{pre:!0,attrs:{class:"language-cpp"}},[a("code",[a("span",{pre:!0,attrs:{class:"token macro property"}},[t._v("#"),a("span",{pre:!0,attrs:{class:"token directive keyword"}},[t._v("include")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token string"}},[t._v("<piped.hpp>")])]),t._v("\n")])])]),a("p",[t._v("However, this pulls in a number of things you may not want, such as "),a("code",[t._v("<regex>")]),t._v(", which only apply to certain operations.  You can instead pull in separate headers if you choose:")]),t._v(" "),a("div",{staticClass:"language-cpp extra-class"},[a("pre",{pre:!0,attrs:{class:"language-cpp"}},[a("code",[a("span",{pre:!0,attrs:{class:"token macro property"}},[t._v("#"),a("span",{pre:!0,attrs:{class:"token directive keyword"}},[t._v("include")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token string"}},[t._v("<piped/string.hpp>")])]),t._v("\n")])])]),a("p",[t._v("For the purposes of this documentation, examples will just "),a("code",[t._v("#include <piped.hpp>")]),t._v(".")]),t._v(" "),a("h2",{attrs:{id:"On-Namespaces"}},[a("a",{staticClass:"header-anchor",attrs:{href:"#On-Namespaces","aria-hidden":"true"}},[t._v("#")]),t._v(" On Namespaces")]),t._v(" "),a("p",[t._v("A basic example:")]),t._v(" "),a("div",{staticClass:"language-cpp extra-class"},[a("pre",{pre:!0,attrs:{class:"language-cpp"}},[a("code",[a("span",{pre:!0,attrs:{class:"token macro property"}},[t._v("#"),a("span",{pre:!0,attrs:{class:"token directive keyword"}},[t._v("include")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token string"}},[t._v("<vector>")])]),t._v("\n"),a("span",{pre:!0,attrs:{class:"token macro property"}},[t._v("#"),a("span",{pre:!0,attrs:{class:"token directive keyword"}},[t._v("include")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token string"}},[t._v("<piped.hpp>")])]),t._v("\n\n"),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("using")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("namespace")]),t._v(" piped"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n\n"),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("auto")]),t._v(" v "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("=")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("from_to")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token number"}},[t._v("0")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(",")]),a("span",{pre:!0,attrs:{class:"token number"}},[t._v("5")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("|")]),t._v(" collect"),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("<")]),t._v("std"),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("::")]),t._v("vector"),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v(">")]),t._v("\n")])])]),a("p",[t._v("You are "),a("em",[t._v("not")]),t._v(" required, of course, to dump this namespace entirely the global namespace.  The alternative:")]),t._v(" "),a("div",{staticClass:"language-cpp extra-class"},[a("pre",{pre:!0,attrs:{class:"language-cpp"}},[a("code",[a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("using")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("namespace")]),t._v(" piped"),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("::")]),t._v("operators"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("   "),a("span",{pre:!0,attrs:{class:"token comment"}},[t._v("// Only the definitions for operator| and |=")]),t._v("\n"),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("namespace")]),t._v(" pd "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("=")]),t._v(" piped"),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n\n"),a("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("auto")]),t._v(" v "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("=")]),t._v(" pd"),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("::")]),a("span",{pre:!0,attrs:{class:"token function"}},[t._v("from_to")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),a("span",{pre:!0,attrs:{class:"token number"}},[t._v("0")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(",")]),a("span",{pre:!0,attrs:{class:"token number"}},[t._v("5")]),a("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v(" "),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("|")]),t._v(" pd"),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("::")]),t._v("collect"),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("<")]),t._v("std"),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v("::")]),t._v("vector"),a("span",{pre:!0,attrs:{class:"token operator"}},[t._v(">")]),t._v("\n")])])]),a("p",[t._v("But for the purposes of this documentation, for brevity and clarity, I will assume we have "),a("code",[t._v("using namespace piped;")]),t._v(".")])])},[],!1,null,null,null);s.default=n.exports}}]);