function fixFunction(ns, m) {
    m.name = ns.name + '::' + m.name;
    m.$refid = m.$refid.replace(/_[0-9a-z]+$/, '');
}

function cmp(a,b) {
    if(a < b) return -1;
    if(a > b) return 1;
    return 0;
}

module.exports = {
    include: [],

    options: {
        htmlescape: false,
    },

    rules: {
        classes: {
            match: "doxygenindex.compound[*$kind = struct | $kind = class]",
        },

        functions: {
            match: "doxygenindex.compound[*$kind = namespace]",

            process: [
                {
                    type: "foldResult",
                    initial: [],
                    foldResult: function(a,b) {
                        if(Array.isArray(b.member)) {
                            for(let m of b.member)
                                fixFunction(b, m);

                            return [...a, ...b.member];
                        }

                        if(b.member) {
                            fixFunction(b, b.member);
                            return [...a, b.member];
                        }

                        return a;
                    },
                },

                {
                    type: "sortResult",
                    sortResult: function(a,b) {
                        return cmp(a.name,b.name);
                    }
                },
            ],
        },

        index: {
            process: [
                { type: "mergeData",
                  mergeData: ["classes", "functions"]
                },
            ],
        },
    },
}
