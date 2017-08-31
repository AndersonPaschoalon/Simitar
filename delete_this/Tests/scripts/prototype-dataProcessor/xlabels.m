
clear

## init demo plot
clf
plot(1:4);

#xticklabel=["aaaaa";"bbbbbbbbbb";"c";"dd"];
xticklabel=["aaaaa";"b";"ccccccccc";"dss"];

fig_gca = gca;

#xtick=[1 2 3 4];
xtick = 1:size(xticklabel,1)
set(fig_gca,'xtick',xtick);

set(fig_gca,'xticklabel',xticklabel);

## get position of current xtick labels
h = get(fig_gca,'xlabel');
xlabelstring = get(h,'string');
xlabelposition = get(h,'position');

## construct position of new xtick labels
yposition = xlabelposition(2);
yposition = repmat(yposition,length(xtick),1);

## disable current xtick labels
set(fig_gca,'xtick',[]);

## set up new xtick labels and rotate
hnew = text(xtick, yposition, xticklabel);
set(hnew,'rotation',45,'horizontalalignment','right');