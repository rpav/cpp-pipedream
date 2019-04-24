function simplifyName(name) {
    name = name.replace(/[: ,<>()=_]/g,'-');
    name = name.replace(/-+/g, '-');
    name = name.replace(/(^-+|-+$)/g, '');
    name = name.replace(/\"/g,'dq');
    name = name.replace(/[{};.?+]/g,'');
    name = name.replace(/[*]/g,'st');
    name = name.replace(/[&]/g,'amp');
    return name;
}


module.exports = {
    title: 'cpp-pipedream',
    base: '/cpp-pipedream/',

    themeConfig: {
        sidebarDepth: 2,
        sidebar: [
            ['/', 'Introduction'],
            '/doc/setup',
            '/doc/basics',
            '/doc/building',
            '/doc/generators',

            {
                title: 'API',
                sidebarDepth: 1,
                children: [
                    [ 'api/group__container', 'Container' ],
                    [ 'api/group__dev', 'Developer Utility' ],
                    [ 'api/group__generator', 'Generators' ],
                    [ 'api/group__mapping', 'Mapping' ],
                    [ 'api/group__match', 'Matching and Replacing' ],
                    [ 'api/group__regex', 'Regex' ],
                    [ 'api/group__string', 'String' ],
                    [ 'api/group__type__util', 'Type Utility' ],
                ],
            },

            '/api/',
        ],
    },

    markdown: {
        extendMarkdown: md => {
            md.use(require('markdown-it-vuepress-code-snippet-enhanced'));
        },

        slugify: s => {
            let simplified = simplifyName(s);
            return simplified;
        },
    },

    evergreen: true,
};
