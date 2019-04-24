module.exports = {
    include: [
        "markup/markdown.json",
    ],

    options: {
        htmlescape: false,
    },

    hacks: ["doxygen", "simpleRefs"],

    processes: {
        text: [
            { type: "textfilter",
              textfilter: {
                  "briefdescription":true,
                  "detaileddescription":true,
                  "description":true
              },
            }
        ],
    },

    rules: {
        doc: {
            match: "doxygen.compounddef",
            process: ["text"],
        },

        members: {
            match: "doxygen.compounddef.sectiondef.memberdef[*$kind=variable | $kind=function][*$prot=public]",
        },

        classes: {
            match: "doxygen.compounddef.innerclass",
            process: [
                { type: "import",
                  import: "$refid",
                },
            ],
        }
    }
}
