(window.webpackJsonp=window.webpackJsonp||[]).push([[13],{48:function(t,a,s){"use strict";s.r(a);var e=s(0),r=Object(e.a)({},function(){var t=this,a=t.$createElement,s=t._self._c||a;return s("ContentSlotsDistributor",{attrs:{"slot-key":t.$parent.slotKey}},[s("h1",{attrs:{id:"Mapping-related-operations"}},[s("a",{staticClass:"header-anchor",attrs:{href:"#Mapping-related-operations","aria-hidden":"true"}},[t._v("#")]),t._v(" Mapping-related operations")]),t._v(" "),s("p",[t._v("Mapping values to other values.")]),t._v(" "),s("table",[s("thead",[s("tr",[s("th",[t._v("Name")]),t._v(" "),s("th",[t._v("Description")])])]),t._v(" "),s("tbody",[s("tr",[s("td",[s("a",{attrs:{href:"#map-to"}},[s("tt",[t._v("map_to")])],1)]),t._v(" "),s("td",[t._v("Map inputs to a new type.")])]),t._v(" "),s("tr",[s("td",[s("a",{attrs:{href:"#F-map-const-F-ampf"}},[s("tt",[t._v("map(const F &f)")])],1)]),t._v(" "),s("td",[t._v("Value generated from "),s("code",[t._v("f(input)")]),t._v(".")])]),t._v(" "),s("tr",[s("td",[s("a",{attrs:{href:"#map-nth-size-t-nth"}},[s("tt",[t._v("map_nth(size_t nth)")])],1)]),t._v(" "),s("td",[t._v("Produce the nth value of input using "),s("code",[t._v("operator[]")]),t._v(".")])])])]),t._v(" "),s("table",[s("thead",[s("tr",[s("th",[t._v("Class")]),t._v(" "),s("th",[t._v("Description")])])]),t._v(" "),s("tbody",[s("tr",[s("td",[s("a",{attrs:{href:"structpiped_1_1adl__map__to"}},[s("tt",[t._v("piped::adl_map_to")])],1)]),t._v(" "),s("td",[t._v("This is used to customize type conversion.")])])])]),t._v(" "),s("h2",{attrs:{id:"T-map-to"}},[s("a",{staticClass:"header-anchor",attrs:{href:"#T-map-to","aria-hidden":"true"}},[t._v("#")]),t._v(" "),s("code",[t._v("<T> map_to")])]),t._v(" "),s("h3",{attrs:{id:"piped/maphpp"}},[s("a",{staticClass:"header-anchor",attrs:{href:"#piped/maphpp","aria-hidden":"true"}},[t._v("#")]),t._v(" "),s("code",[t._v("<piped/map.hpp>")])]),t._v(" "),s("div",{staticClass:"language-cpp extra-class"},[s("pre",{pre:!0,attrs:{class:"language-cpp"}},[s("code",[s("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("template")]),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("<")]),s("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("typename")]),t._v(" T"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v(">")]),t._v("\n"),s("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("constexpr")]),t._v(" detail"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("::")]),t._v("map_to_"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("<")]),t._v("T"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v(">")]),t._v(" piped"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("::")]),t._v("map_to\n")])])]),s("h3",{attrs:{id:"Description"}},[s("a",{staticClass:"header-anchor",attrs:{href:"#Description","aria-hidden":"true"}},[t._v("#")]),t._v(" Description")]),t._v(" "),s("p",[t._v("Map inputs to a new type.")]),t._v(" "),s("p",[t._v("By default, this is a "),s("code",[t._v("static_cast<To>")]),t._v(". See adl_map_to for customizing this.")]),t._v(" "),s("p",[t._v("Example:")]),t._v(" "),s("div",{staticClass:"language-cpp extra-class"},[s("pre",{pre:!0,attrs:{class:"language-cpp"}},[s("code",[s("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("auto")]),t._v(" v "),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("=")]),t._v(" "),s("span",{pre:!0,attrs:{class:"token string"}},[t._v('"a,b,c"')]),t._v(" "),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("|")]),t._v(" "),s("span",{pre:!0,attrs:{class:"token function"}},[t._v("split")]),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),s("span",{pre:!0,attrs:{class:"token string"}},[t._v('","')]),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v(" "),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("|")]),t._v(" map_to"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("<")]),t._v("std"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("::")]),t._v("string"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v(">")]),t._v(" "),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("|")]),t._v(" collect"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("<")]),t._v("std"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("::")]),t._v("vector"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v(">")]),t._v("\n"),s("span",{pre:!0,attrs:{class:"token comment"}},[t._v("// Produces a vector<string>, creating new strings,")]),t._v("\n"),s("span",{pre:!0,attrs:{class:"token comment"}},[t._v("// rather than a vector<string_view>")]),t._v("\n")])])]),s("h2",{attrs:{id:"F-map-const-F-ampf"}},[s("a",{staticClass:"header-anchor",attrs:{href:"#F-map-const-F-ampf","aria-hidden":"true"}},[t._v("#")]),t._v(" "),s("code",[t._v("<F> map(const F &f)")])]),t._v(" "),s("h3",{attrs:{id:"piped/maphpp-2"}},[s("a",{staticClass:"header-anchor",attrs:{href:"#piped/maphpp-2","aria-hidden":"true"}},[t._v("#")]),t._v(" "),s("code",[t._v("<piped/map.hpp>")])]),t._v(" "),s("div",{staticClass:"language-cpp extra-class"},[s("pre",{pre:!0,attrs:{class:"language-cpp"}},[s("code",[s("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("template")]),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("<")]),s("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("typename")]),t._v(" F"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v(">")]),t._v("\ndetail"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("::")]),t._v("map_"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("<")]),t._v("F"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v(">")]),t._v(" piped"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("::")]),s("span",{pre:!0,attrs:{class:"token function"}},[t._v("map")]),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),s("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("const")]),t._v(" F "),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("&")]),t._v("f"),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v("\n")])])]),s("h3",{attrs:{id:"Description-2"}},[s("a",{staticClass:"header-anchor",attrs:{href:"#Description-2","aria-hidden":"true"}},[t._v("#")]),t._v(" Description")]),t._v(" "),s("p",[t._v("Value generated from "),s("code",[t._v("f(input)")]),t._v(".")]),t._v(" "),s("p",[t._v("Example:")]),t._v(" "),s("div",{staticClass:"language-cpp extra-class"},[s("pre",{pre:!0,attrs:{class:"language-cpp"}},[s("code",[s("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("auto")]),t._v(" v "),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("=")]),t._v(" "),s("span",{pre:!0,attrs:{class:"token function"}},[t._v("from_to")]),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),s("span",{pre:!0,attrs:{class:"token number"}},[t._v("1")]),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(",")]),s("span",{pre:!0,attrs:{class:"token number"}},[t._v("4")]),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v("\n  "),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("|")]),t._v(" "),s("span",{pre:!0,attrs:{class:"token function"}},[t._v("map")]),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("[")]),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("]")]),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),s("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("auto")]),t._v(" v"),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v(" "),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("{")]),t._v(" "),s("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("return")]),t._v(" v "),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("+")]),t._v(" "),s("span",{pre:!0,attrs:{class:"token number"}},[t._v("1")]),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v(" "),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("}")]),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v("\n  "),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("|")]),t._v(" collect"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("<")]),t._v("std"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("::")]),t._v("vector"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v(">")]),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n\n"),s("span",{pre:!0,attrs:{class:"token comment"}},[t._v("/// Produces [2,3,4] as a vector<int>")]),t._v("\n")])])]),s("table",[s("thead",[s("tr",[s("th",[t._v("Parameter")]),t._v(" "),s("th"),t._v(" "),s("th")])]),t._v(" "),s("tbody",[s("tr",[s("td",[s("code",[t._v("f")])]),t._v(" "),s("td",[s("code",[t._v("const F &")])]),t._v(" "),s("td")])])]),t._v(" "),s("h2",{attrs:{id:"map-nth-size-t-nth"}},[s("a",{staticClass:"header-anchor",attrs:{href:"#map-nth-size-t-nth","aria-hidden":"true"}},[t._v("#")]),t._v(" "),s("code",[t._v("map_nth(size_t nth)")])]),t._v(" "),s("h3",{attrs:{id:"piped/maphpp-3"}},[s("a",{staticClass:"header-anchor",attrs:{href:"#piped/maphpp-3","aria-hidden":"true"}},[t._v("#")]),t._v(" "),s("code",[t._v("<piped/map.hpp>")])]),t._v(" "),s("div",{staticClass:"language-cpp extra-class"},[s("pre",{pre:!0,attrs:{class:"language-cpp"}},[s("code",[t._v("detail"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("::")]),t._v("map_nth_ piped"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("::")]),s("span",{pre:!0,attrs:{class:"token function"}},[t._v("map_nth")]),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),t._v("size_t nth"),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v("\n")])])]),s("h3",{attrs:{id:"Description-3"}},[s("a",{staticClass:"header-anchor",attrs:{href:"#Description-3","aria-hidden":"true"}},[t._v("#")]),t._v(" Description")]),t._v(" "),s("p",[t._v("Produce the nth value of input using "),s("code",[t._v("operator[]")]),t._v(".")]),t._v(" "),s("p",[t._v("Example:")]),t._v(" "),s("div",{staticClass:"language-cpp extra-class"},[s("pre",{pre:!0,attrs:{class:"language-cpp"}},[s("code",[s("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("auto")]),t._v(" s "),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("=")]),t._v(" "),s("span",{pre:!0,attrs:{class:"token string"}},[t._v('"X:Y:Z:"')]),t._v("s"),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n"),s("span",{pre:!0,attrs:{class:"token keyword"}},[t._v("auto")]),t._v(" v "),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("=")]),t._v(" s\n  "),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("|")]),t._v(" "),s("span",{pre:!0,attrs:{class:"token function"}},[t._v("each_match")]),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),s("span",{pre:!0,attrs:{class:"token string"}},[t._v('".:"')]),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v("             "),s("span",{pre:!0,attrs:{class:"token comment"}},[t._v("// match_data")]),t._v("\n  "),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("|")]),t._v(" "),s("span",{pre:!0,attrs:{class:"token function"}},[t._v("map_nth")]),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v("(")]),s("span",{pre:!0,attrs:{class:"token number"}},[t._v("0")]),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(")")]),t._v("                   "),s("span",{pre:!0,attrs:{class:"token comment"}},[t._v("// nth submatch")]),t._v("\n  "),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("|")]),t._v(" map_to"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("<")]),t._v("std"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("::")]),t._v("string_view"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v(">")]),t._v("\n  "),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("|")]),t._v(" collect"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("<")]),t._v("std"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v("::")]),t._v("vector"),s("span",{pre:!0,attrs:{class:"token operator"}},[t._v(">")]),s("span",{pre:!0,attrs:{class:"token punctuation"}},[t._v(";")]),t._v("\n\n"),s("span",{pre:!0,attrs:{class:"token comment"}},[t._v('// Produce ["X:", "Y:", "Z:"] as a `vector<string_view>`')]),t._v("\n")])])]),s("table",[s("thead",[s("tr",[s("th",[t._v("Parameter")]),t._v(" "),s("th"),t._v(" "),s("th")])]),t._v(" "),s("tbody",[s("tr",[s("td",[s("code",[t._v("nth")])]),t._v(" "),s("td",[s("code",[t._v("size_t")])]),t._v(" "),s("td")])])])])},[],!1,null,null,null);a.default=r.exports}}]);