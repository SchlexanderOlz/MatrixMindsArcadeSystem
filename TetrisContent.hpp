#pragma once

constexpr char* tetris_XML = R"(<Tetris>
  <box id="main-box" x="0.23" y="0.0" width="1.34" height="1.8"></box>
  <box id="next-box" x="-0.75" y="0.68" width="0.45" height="0.5"></box>
  <!-- To include text doesnt make any sense at this scale. Either remove this dynamically in the future or just keep it static as-is -->
  <!-- <text id="shape-name" x="-0.9" y="0.0">Shapename</text> -->
</Tetris>
)";