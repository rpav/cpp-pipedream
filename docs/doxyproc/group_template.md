# {{doc.title}}

{{doc.briefdescription}}

{{doc.detaileddescription}}

{{#if members}}
| Name | Description |
|------|-------------|
{{#members}}
| <a href="#{{_ref}}"><tt>{{name}}{{argsstring}}</tt></a> | {{briefdescription}} |
{{/members}}
{{/if}}

{{#if classes}}
| Class | Description |
|-------|-------------|
{{#classes}}
| <a href="{{$refid}}"><tt>{{$$}}</tt></a> | {{doxygen.compounddef.briefdescription}} |
{{/classes}}
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

{{#if return}}
| Returns |
|:--------|
|{{return.description}}|
{{/if}}

{{#if param}}
| Parameter | | |
|---|---|---|
{{#param}}
| `{{declname}}` | `{{type}}` | {{description}} |
{{/param}}
{{/if}}


{{/members}}
