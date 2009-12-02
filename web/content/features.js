var c_features = "<h2>Features</h2> \
<p>What makes Rising Tide so great?</p> \
	<ul> \
		<li><strong>Complex viewport behavior</strong> - the viewport is player-dependent in the x-direction \
		and moves at a constant rate in the y-direction.  The viewport's y-motion can also be paused or adjusted \
		to move at any velocity.</li> \
		<li><strong>Encapsulated design</strong> - all SDL-related behavior occurs in the game manager, camera, \
		and world.  No sprites blit themselves or perform any surface-related operations.</li> \
		<li><strong>Advanced resource managers</strong> - singleton resource manager classes exist to manage \
		images, music, and fonts to prevent images from being needlessly loaded multiple times.  Instead, instances \
		are cached for later use and can easily be freed at program termination.</li> \
		<li><strong>Custom map parsing</strong> - game levels are read in from special .map files that describe \
		the presence of blocks and the hovercraft.  Level files can currently be passed in as a parameter to \
		the executable.</li>\
		<li><strong>A critically acclaimed soundtrack</strong> - borrowed from renowned sources including the \
		Windows XP soundtrack and the Internet, the musical score launches players into the catastrophic world \
		of Rising Tide. \
	</ul>";
