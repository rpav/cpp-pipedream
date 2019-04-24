# `{{doc.compoundname}}`

## `<{{doc.location.$file}}>`
```cpp
{{doc.templatestring}}{{doc.$kind}} {{doc.compoundname}};
```

{{doc.briefdescription}}

{{doc.detaileddescription}}

{{#if members}}
| Name | Description |
|------|-------------|
{{#members}}
| <a href="#{{_ref}}"><tt>{{name}}{{argsstring}}</tt></a> | {{briefdescription}} |
{{/members}}

# Members
{{/if}}

{{#members}}
## `{{templateshortstring}}{{name}}{{argsstring}}`
### `<{{location.$file}}>`
```cpp
{{templatestring}}{{definition}}{{argsstring}}
```

### Description
{{briefdescription}}

{{detaileddescription}}

{{#if param}}
| Parameter | | |
|---|---|---|
{{#param}}
| `{{declname}}` | `{{type}}` | {{description}} |
{{/param}}
{{/if}}
{{/members}}
